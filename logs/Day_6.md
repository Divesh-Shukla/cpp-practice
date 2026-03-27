## Day 6 — March 20, 2026
### Topic: Memory Layout — Stack, Heap, Data, Text

---

## Retrieval Warm-Up

**Q1. What three things does a stack frame store?**
Arguments, local variables, and the return address (where to resume execution after the function returns).

**Q2. What is the difference between `-g` and `-O2`?**
`-g` embeds debug symbols (line numbers, variable names) into the binary — required for gdb to show meaningful output. `-O2` applies aggressive optimization: inlines functions, eliminates variables, reorders instructions. Even with `-g` added, an `-O2` build is effectively undebuggable because variables show as `<optimized out>` and execution order doesn't match source. Always develop with `-g -O0`, ship with `-O2`.

**Q3. What does `bt` show in gdb, and what does each frame represent?**
`bt` prints the active call stack at the point of crash. Each frame represents one function call — showing the function name, arguments, and source location.

---

## Key Concepts

### The Four Memory Regions

```
High address
┌─────────────────┐
│      STACK      │  ← local variables, arguments, return addresses
│        ↓        │  grows downward
├─────────────────┤
│                 │  unused space
│        ↑        │
│      HEAP       │  ← malloc'd memory, grows upward
├─────────────────┤
│      DATA       │  ← global variables, static variables
├─────────────────┤
│      TEXT       │  ← compiled machine instructions (read-only)
└─────────────────┘
Low address
```

| Region | What lives there | Who manages it | Lifetime |
|---|---|---|---|
| TEXT | Compiled code | Compiler | Program duration |
| DATA | Globals, statics | Compiler | Program duration |
| HEAP | malloc'd memory | Programmer | Until `free()` is called |
| STACK | Locals, arguments | CPU/compiler | Until function returns |

---

### Scope vs Lifetime (K.N. King Chapter 18)

- **Scope** — the region of code where a variable can be accessed
- **Lifetime (storage duration)** — how long the memory reserved for a variable exists before being freed
- **Automatic storage duration** — variable lives as long as its block is active (stack)
- **Static storage duration** — variable lives for the entire duration of the program (DATA segment)

---

### ASLR — Address Space Layout Randomization
The OS randomizes where the stack and heap are placed in memory on each program run. This is a security feature — it makes memory addresses unpredictable for attackers. The *relative* relationships remain constant: stack is always high, heap is always low.

---

### Heap Allocation Overhead
`malloc(sizeof(int))` asks for 4 bytes but the allocator returns a 16-byte chunk. The extra bytes store allocator metadata: size of the block, whether it's free or in use, and pointers for the free list. This is why consecutive `malloc` calls produce addresses 16 bytes apart, not 4.

---

## Programs Written and Observed

### Program 1 — Pointer modifying stack variable
```c
int x = 10;
int* p = &x;
*p = 20;
printf("%d\n", x);  // prints 20
```
Both `x` and `p` live on the stack. `p` stores the address of `x`. `*p = 20` follows the address and writes 20 into `x`.

---

### Program 2 — Stack frame reuse
```c
void foo(){
    int local = 5;
    printf("%p\n", &local);
}
int main(){
    foo();
    foo();
}
```
**Output:** same address both times.

First call pushes a frame at address X, function returns, stack pointer moves back up. Second call pushes a frame at the same position — identical address. Stack frames are reused when the call depth is the same.

---

### Program 3 — Dangling pointer (undefined behavior)
```c
int* dangerous(){
    int local = 42;
    return &local;
}
int main(){
    int* p = dangerous();
    printf("%p\n", p);  // DO NOT dereference
}
```
`local` lives on the stack inside `dangerous()`. When the function returns, its frame is popped — the memory is freed. `p` now holds the address of dead memory.

**Observed:** compiler detected the UB with `-Wreturn-local-addr` warning and nulled the pointer — printed `(nil)`. This is UB in action: same source code, different compiler behavior depending on flags and optimization level.

---

### Program 4 — Static vs local storage duration
```c
void counter(){
    static int s = 0;
    int local = 0;
    s++; local++;
    printf("static: %d, local: %d\n", s, local);
}
int main(){
    counter(); counter(); counter();
}
```
**Output:**
```
static: 1, local: 1
static: 2, local: 1
static: 3, local: 1
```
`s` lives in DATA — allocated once, persists across calls, increments each time. `local` lives on the stack — new frame each call, reinitialized to 0 every time, always prints 1.

---

### Problem — Stack vs Heap addresses
Allocated 5 ints on stack and 5 via `malloc`. Printed all addresses.

**Stack:** `0x7fff...` — high addresses, 4 bytes apart (contiguous in frame)
**Heap:** `0x55...` — completely different range, 16 bytes apart (allocator overhead)

**Valgrind result before fix:** `definitely lost: 16 bytes in 4 blocks` — freed only 1 of 5 pointers.
**Valgrind result after fix:** `0 errors from 0 contexts — All heap blocks were freed` ✅

---

## Conceptual Exit Question

**A function returns a pointer to a local variable. The caller dereferences it. Describe exactly what has happened in memory between the return and the dereference. Why is the result undefined rather than just wrong?**

The local variable has automatic storage duration — its stack frame is popped the moment the function returns. The pointer the caller holds now points to freed stack memory. By the time the caller dereferences it, that memory may have been overwritten by another function call, still contain the old value by coincidence, or be in any other state. The result is undefined — not just wrong — because the compiler makes no guarantee whatsoever about what is at that address. It could crash, return a stale value, silently corrupt data, or behave differently across compiler versions and optimization levels. UB gives the compiler permission to assume this never happens, and optimize accordingly — which is why the behavior is unpredictable rather than consistently wrong.