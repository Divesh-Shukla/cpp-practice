# Day 11 — 26 March, 2026
## Topic: Const Correctness + Undefined Behavior & Sanitizers

---

## Implementations

### Const Correctness

#### Task 1: Observe compiler error when modifying an object pointed by `const int* p`
**Error:**
```bash
Assignment of read only location `*p`.
                        *p = 6;
                           ^
```

#### Task 2: Observe the compiler error when modifying a pointer whose declaration is `int* const p`
**Error:**
```bash
Assignment of read only location `p`.
                         p = &y;
                           ^
```

#### Task 3 and 4: Passing string to function as `const char*` — correct signature and implementing strlen using the same
**Code:**
```c
size_t my_strlen(const char* s)
{
    size_t counter = 0;
    while(*s != '\0')
    {
        s++;
        counter++;
    }
    return counter;
}
```

#### Task 5: Implement const-correct `my_strcmp` — `int my_strcmp(const char *a, const char *b)`
**Code:**
```c
int my_strcmp(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0')
    {
        if (*a != *b)
        {
            return *a - *b;
        }
        a++;
        b++;
    }
    return *a - *b;
}
```
*Note: loop condition must be `&&` not `||` — with `||`, if one string ends first, you keep looping into garbage memory.*

---

### Full Const-Correct String Library

Final implementations with complete test suite:

```c
#include<stdio.h>

size_t my_strlen(const char *c)
{
    size_t counter = 0;
    while (*c)
    {
        c++;
        counter++;
    }
    return counter;
}

int my_strcmp(const char *a, const char *b)
{
    while (*a != '\0' && *b != '\0')
    {
        if(*a != *b) return *a - *b;
        a++;
        b++;
    }
    return *a - *b;
}

char* my_strcpy(char* dest, const char* src)
{
    char* temp = dest;
    while (*src != 0)
    {
        *temp++ = *src++;
    }
    *temp = '\0';
    return dest;
}

char* my_strcat(char* dest, const char* src)
{
    char* temp = dest;
    while (*dest != '\0') dest++;
    while (*src != '\0') *dest++ = *src++;
    *dest = '\0';
    return temp;
}
```

**Test suite — all four functions tested against edge cases and verified against standard library:**

```c
void test_strlen() {
    printf("\n==== Testing my_strlen ====\n");
    printf("Empty: %zu\n", my_strlen(""));
    printf("Single char: %zu\n", my_strlen("A"));
    printf("Normal: %zu\n", my_strlen("Hello World"));
    printf("Spaces: %zu\n", my_strlen("   "));
}

void test_strcmp() {
    printf("\n==== Testing my_strcmp ====\n");
    printf("Equal: %d\n", my_strcmp("abc", "abc"));
    printf("a < b: %d\n", my_strcmp("abc", "abd"));
    printf("a > b: %d\n", my_strcmp("abe", "abd"));
    printf("Prefix (shorter): %d\n", my_strcmp("abc", "abcd"));
    printf("Prefix (longer): %d\n", my_strcmp("abcd", "abc"));
    printf("Empty vs empty: %d\n", my_strcmp("", ""));
    printf("Empty vs non-empty: %d\n", my_strcmp("", "a"));
    printf("Non-empty vs empty: %d\n", my_strcmp("a", ""));
    char s1[] = "\xFF";
    char s2[] = "\x01";
    printf("High ASCII compare: %d\n", my_strcmp(s1, s2));
}

void test_strcpy() {
    printf("\n==== Testing my_strcpy ====\n");
    char dest[50];
    my_strcpy(dest, "Hello");
    printf("Copy 'Hello': %s\n", dest);
    my_strcpy(dest, "");
    printf("Copy empty: '%s'\n", dest);
    my_strcpy(dest, "First");
    my_strcpy(dest, "Second");
    printf("Overwrite test: %s\n", dest);
    my_strcpy(dest, "This is a longer string test");
    printf("Long copy: %s\n", dest);
}

void test_strcat() {
    printf("\n==== Testing my_strcat ====\n");
    char buffer[100] = "Hello";
    my_strcat(buffer, " World");
    printf("Append: %s\n", buffer);
    my_strcat(buffer, "!!!");
    printf("Multiple append: %s\n", buffer);
    my_strcat(buffer, "");
    printf("Append empty: %s\n", buffer);
    char empty[50] = "";
    my_strcat(empty, "Start");
    printf("Empty dest: %s\n", empty);
}
```

All four functions match standard library output. Valgrind clean.

---

## UB & Sanitizers

### Task 6: Null pointer dereference → catch with ASan
**Code:**
```c
int *p = NULL;
*p = 5;
```

**Command:** `gcc -fsanitize=address -g implementD11.c -o implementD11`

**Error:**
```bash
AddressSanitizer:DEADLYSIGNAL
=================================================================
==27087==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x59d2a01413ca bp 0x7ffe2769b9b0 sp 0x7ffe2769b9a0 T0)
==27087==The signal is caused by a WRITE memory access.
==27087==Hint: address points to the zero page.
    #0 0x59d2a01413ca in main implementD11.c:34
```

**Reading the error:**
- `SEGV on unknown address 0x000000000000` — segmentation fault at address 0. That address IS NULL.
- `The signal is caused by a WRITE memory access` — the fault was triggered by a write attempt, not a read.
- `address points to the zero page` — the zero page (address 0x0) is intentionally unmapped by the OS precisely to catch null dereferences. Any access to it is immediately killed.

---

### Task 7: Out-of-bounds array access → catch with ASan and UBSan

**Code:**
```c
int arr[10] = {0};
arr[50] = 99;
printf("%d\n", arr[50]);
```

**ASan result:** No error reported. Program ran and printed output.

**UBSan result:**
```bash
implementD11.c:32:8: runtime error: index 50 out of bounds for type 'int [10]'
implementD11.c:32:13: runtime error: store to address 0x7fff0dfe4de8 with insufficient space for an object of type 'int'
implementD11.c:33:23: runtime error: index 50 out of bounds for type 'int [10]'
implementD11.c:33:5: runtime error: load of address 0x7fff0dfe4de8 with insufficient space for an object of type 'int'
99
```

**Reading the error:**
1. `runtime error: index 50 out of bounds for type 'int [10]'` — index 50 exceeds the declared array size of 10.
2. `runtime error: store to address 0x7fff0dfe4de8 with insufficient space for an object of type 'int'` — attempted to store at an address that isn't validly allocated for an int.
3. `runtime error: load of address 0x7fff0dfe4de8 with insufficient space for an object of type 'int'` — attempted to read from the same invalid address.
4. **The program still printed `99` — correct output.** First run luck. Second run printed `1659715328` — garbage. *The first time was luck, the second was an eventuality.*

This is the essence of UB: not a crash, not a wrong answer, not a right answer — anything can happen and it is impossible to predict.

---

**Second implementation — `arr[10]` (off by one):**
```c
int arr[10] = {0};
arr[10] = 99;
```

**ASan result:**
```bash
=================================================================
==29160==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7f7b1c800058
WRITE of size 4 at 0x7f7b1c800058 thread T0
    #0 0x5b0d59d1757d in main implementD11.c:32

  This frame has 1 object(s):
    [48, 88) 'arr' (line 31) <== Memory access at offset 88 overflows this variable
```

**Reading the error:**
1. `ERROR: AddressSanitizer: stack-buffer-overflow` — local variable (`stack`), written past its end (`buffer-overflow`).
2. `WRITE of size 4` — attempted to write 4 bytes (one int) into invalid memory.
3. `implementD11.c:32` — exact line of the violation.
4. `[48, 88) 'arr'` — arr occupies memory offsets 48 to 88 within the stack frame. Access at offset 88 is one byte past the end. Off by one — caught.

**Shadow memory map:**
```
=>0x7f7b1c800000: f1 f1 f1 f1 f1 f1 00 00 00 00 00[f3]f3 f3 f3 f3
```
- `00` = addressable memory (the array)
- `f1` = stack left redzone
- `f3` = stack right redzone — the `[f3]` is the exact byte hit by `arr[10]`

**Why ASan caught `arr[10]` but not `arr[50]`:**
1. ASan surrounds stack variables with poisoned guard regions called redzones.
2. Access is tracked via shadow memory — 1 shadow byte represents 8 real bytes.
3. `arr[10]` lands immediately past the array, directly into the right redzone (`f3`) — detected.
4. `arr[50]` jumps far beyond, skipping the redzones entirely into unpoisoned memory — not detected.
5. Detection depends on where the invalid access lands, not just that it is invalid.
6. Small overflows → high detection probability. Large jumps → may evade ASan entirely.
7. UBSan, by contrast, checks semantic bounds at the source level — it always flags `arr[50]` regardless of where in memory it lands.

**Lesson: ASan and UBSan are complementary. Use both.**

---

### Task 8: Use-after-free → catch with ASan
**Code:**
```c
int *arr = malloc(sizeof(int));
*arr = 6;
free(arr);
*arr = 6;  // use after free
```

**Command:** `gcc -fsanitize=address -g implementD11.c -o implementD11 && ./implementD11`

**Error:**
```bash
=================================================================
==30219==ERROR: AddressSanitizer: heap-use-after-free on address 0x502000000010
WRITE of size 4 at 0x502000000010 thread T0
    #0 0x5d12e347544a in main implementD11.c:35

0x502000000010 is located 0 bytes inside of 4-byte region [0x502000000010,0x502000000014)
freed by thread T0 here:
    #1 0x5d12e3475413 in main implementD11.c:34

previously allocated by thread T0 here:
    #1 0x5d12e34753c2 in main implementD11.c:32
```

**Reading the error:**
1. `heap-use-after-free` — write or read on heap memory that has already been freed.
2. `WRITE of size 4` — attempted to write an int (4 bytes) into freed memory.
3. `implementD11.c:35` — exact line of the violation (the second `*arr = 6`).
4. `freed by thread T0 here: implementD11.c:34` — the `free(arr)` call that released ownership.
5. `previously allocated by thread T0 here: implementD11.c:32` — the original `malloc` that created the block.
6. `0x502000000010 is located 0 bytes inside of 4-byte region` — accessed exactly the start of the freed block, not some offset into it.

**Shadow map:**
```
=>0x502000000000: fa fa[fd]fa fa fa fa fa fa fa fa fa fa fa fa fa
```
- `fa` = heap redzone (surrounding guard)
- `fd` = freed heap region — the `[fd]` is the exact byte hit

ASan marks freed regions as poisoned (`fd`). Any subsequent access to that region is caught immediately, with a full report of where it was allocated, where it was freed, and where it was illegally accessed.

---

### Task 9: Signed integer overflow — `INT_MAX + 1` → catch with UBSan
**Code:**
```c
#include <limits.h>
int x = INT_MAX;
int y = x + 1;
```

**Command:** `gcc -fsanitize=undefined -g implementD11.c -o implementD11 && ./implementD11`

**Error:**
```bash
implementD11.c:6:9: runtime error: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int'
```

**Reading the error:**
1. `implementD11.c:6:9` — file, row 6, column 9. Exact location of the overflowing expression.
2. `runtime error: signed integer overflow` — triggered at runtime, not compile time. The compiler doesn't know the runtime value of `x`.
3. `2147483647 + 1 cannot be represented in type 'int'` — `INT_MAX` is 2147483647 (2³¹ − 1). Adding 1 wraps around to a negative number in two's complement — this is defined for unsigned integers but UB for signed integers in C.

---

### Task 10: Uninitialized variable read → catch with MSan
**Code:**
```c
int x;
x += 1;
printf("%d\n", x);
```

**UBSan result:** No error. Printed garbage value silently.

**MSan (clang) result:**
```bash
==34828==WARNING: MemorySanitizer: use-of-uninitialized-value
    #0 0x55555561e380 in main implementD11.c:7:5
```

**Reading the error:**
1. `use-of-uninitialized-value` — a value was read before it was written.
2. `implementD11.c:7:5` — exact line and column of the read.

**Why UBSan missed it:** UBSan instruments specific categories of UB — integer overflow, out-of-bounds indexing, null dereference. Uninitialized reads are not in its scope.

**Why MSan caught it:** MSan (Memory Sanitizer) tracks the initialized/uninitialized state of every byte of memory. It instruments every read and checks whether the source bytes were ever written. This requires clang — gcc does not support `-fsanitize=memory`.

---

## Sanitizer Comparison Table

| Sanitizer | Flag | Catches | Misses |
|---|---|---|---|
| ASan | `-fsanitize=address` | Out-of-bounds (near), use-after-free, double-free, heap/stack overflow | Large out-of-bounds jumps past redzones |
| UBSan | `-fsanitize=undefined` | Integer overflow, index OOB (semantic), null dereference | Uninitialized reads |
| MSan | `-fsanitize=memory` (clang only) | Uninitialized reads | Requires clang, high overhead |

**Standard debug build flags — use always:**
```bash
gcc -Wall -Wextra -g -fsanitize=address -fsanitize=undefined -o program source.c
```

---

## Key Concept

**ASan detects redzone violations — physical guard regions around allocations. UBSan detects semantic violations — language-level rules that C says you cannot break. They catch different classes of bugs. A small overflow evades UBSan but hits ASan's redzone. A large overflow evades ASan but hits UBSan's bounds check. Use both on every debug build.**

---

## Exit Question

*What is the difference between ASan and UBSan? When would you use each?*

ASan instruments memory accesses at runtime. It surrounds every allocation — stack, heap, global — with poisoned guard regions called redzones, and tracks their state via shadow memory. Any access that hits a poisoned region is caught immediately with a full report: what type of violation, exact address, allocation site, free site, and access site. It catches spatial violations — out-of-bounds (near the boundary), use-after-free, double-free.

UBSan instruments arithmetic and type operations at the source level. It inserts checks at compile time that fire at runtime when a language rule is violated — signed integer overflow, array index out of semantic bounds, null pointer dereference. It catches these regardless of where in memory the access physically lands.

They are complementary. `arr[10]` on a 10-element array: ASan catches it because it hits the right redzone. `arr[50]`: ASan may miss it because the jump skips the redzone, but UBSan always catches it because it checks the index against the declared size. Use both flags on every debug build. Neither is a substitute for the other.

*Why can undefined behavior cause a program to appear to work correctly in debug mode but crash in release mode? What is the compiler doing differently?*

- Undefined behaviour can appear to work normally in debug mode because in debug mode the compiler dumb translates the code written in the source code to assembly, therefore in many instances the program can seem to work normally.
-  But in the release mode the compiler assumes that undefined behaviour never  happens so it restrcuctures codes and expression based on that assumption, so the code that comes out of compilation is the optimized and restructured version of the written code and different from it so when running the program, the program behaves differently from what was written!
---

## Confusion

- Why MSan requires clang and not gcc — gcc's instrumentation pipeline does not support the shadow memory tracking MSan needs at the same level clang does.
- Exact internal structure of shadow memory — how 1 shadow byte maps to 8 real bytes and how poisoned states are encoded (partially understood from the `f3`, `fd`, `fa` legend).