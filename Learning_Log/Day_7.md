## Day 7 — March 21, 2026
### Topic: Pointer Fundamentals

---

## Retrieval Warm-Up

**Q1. What are the four memory regions and what lives in each?**
- TEXT — compiled machine instructions, read-only, fixed size
- DATA — global and static variables, lives for entire program duration
- STACK — function stack frames (local variables, arguments, return address), automatic lifetime
- HEAP — dynamically allocated memory via malloc, lives until free() is called

**Q2. What is the difference between automatic and static storage duration?**
Automatic storage duration means the variable lives as long as its code block is executing — allocated on the stack, freed when the function returns. Static storage duration means the variable lives for the entire duration of the program — allocated in DATA segment before main() runs.

**Q3. A function returns a pointer to a local variable. What has happened in memory by the time the caller dereferences it?**
The local variable had automatic storage duration — its stack frame was popped the moment the function returned. The pointer now holds the address of freed stack memory. Dereferencing it is undefined behavior — the memory may have been overwritten, still contain the old value by coincidence, or be in any state. The compiler makes no guarantee.

---

## Key Concepts

### What a Pointer Actually Is
A pointer stores a raw memory address — just a number. The data type attached to the pointer (`int*`, `char*`) is compile-time information only. At runtime, the pointer is just an address — the type doesn't exist in the binary. The type tells the compiler two things:
- How many bytes to read when dereferencing
- How many bytes to jump when doing pointer arithmetic

### Pointer Arithmetic
`p + 1` does not add 1 to the address. It adds `1 * sizeof(type)`. So:
- `int* p`: `p + 1` moves 4 bytes forward
- `char* p`: `p + 1` moves 1 byte forward
- `double* p`: `p + 1` moves 8 bytes forward

This is why pointer arithmetic works correctly for array traversal — each `+1` lands exactly on the next element.

### Pointers as Function Arguments
When you pass a pointer to a function and modify `*p` inside, you are modifying the original variable directly. The pointer holds the address of the original — dereferencing it writes to that address regardless of which function you're in. This is how C achieves pass-by-reference behavior.

### Pointers and Arrays
`int* p = arr` and `int* p = &arr[0]` are identical. An array name decays to a pointer to its first element. `arr[i]` and `*(arr + i)` are also identical — index notation is syntactic sugar for pointer arithmetic.

---

## Code Written

### swap()
```c
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
```
Passes addresses of two variables, swaps values at those addresses. Demonstrates pass-by-pointer.

---

### my_strlen() — pointer arithmetic only
```c
int my_strlen(char *a){
    char *temp = a;
    while (*temp != '\0'){
        temp++;
    }
    return temp - a;
}
```
Two pointers: `a` stays at start, `temp` walks forward until null terminator. Pointer subtraction gives the count. No index, no counter variable.

---

### maxArr()
```c
int *maxArr(int *a, int size){
    int *max = a;
    int *i;
    for (i = a; i < a + size; i++){
        if (*max < *i){
            max = i;
        }
    }
    return max;
}
```
Returns a pointer to the maximum element, not the value. Caller dereferences to get the value.

---

### find()
```c
int *find(int *arr, int size, int target){
    int *end = arr + size;
    while (arr < end){
        if (*arr == target) return arr;
        arr++;
    }
    return NULL;
}
```
**Bug hit:** original condition was `while (arr < arr + size)` — always true because `arr + size` recalculates every iteration using the current (advancing) `arr`. The gap never closes.
**Fix:** save `end` before the loop — `int *end = arr + size` — fixed boundary.

---

### reverseArray() — in place, pointer arithmetic only
```c
void reverseArray(int *a, int size){
    int *temp = a + size - 1;
    while (a < temp){
        swap(a++, temp--);
    }
}
```
**First attempt:** printed array backwards — not in place, wrong approach entirely.
**Final version:** two pointers from opposite ends moving toward each other, swapping at each step, stopping when they meet. Handles odd and even sizes correctly.

---

## Conceptual Exit Question

**What is the difference between `int* p = arr` and `int* p = &arr[0]`? Why does `p + 1` move 4 bytes for `int*` but 1 byte for `char*`? What does this tell you about what a pointer stores?**

`int* p = arr` and `int* p = &arr[0]` are identical — an array name decays to a pointer to its first element, which is exactly what `&arr[0]` gives you.

`p + 1` moves by `sizeof(type)` because the compiler uses the pointer's type to scale the arithmetic. For `int*` that's 4 bytes, for `char*` it's 1 byte. This is compile-time information — at runtime a pointer is just a raw address, a number. The type doesn't exist in the binary. The type exists only so the compiler knows how to interpret reads, writes, and arithmetic on that address.