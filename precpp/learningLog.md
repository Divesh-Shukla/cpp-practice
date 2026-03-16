# Learning Log — C++ & DSA Journey

---

## Day 1 — March 14, 2026
### Topic: Environment Setup + Pointer Baseline

### Environment Setup
- Installed: gcc, g++, gdb, valgrind, make, clang
- First valgrind run: clean (0 errors) on LinkedList code
- Key command: `valgrind --leak-check=full ./binary_name`

### Pointer Baseline (Retrieval Warm-up)
**Q: What does `int* p;` create?**
`p` is a pointer — holds a memory address. Uninitialized means it holds a garbage address. Called a wild pointer.

**Q: Difference between `p` and `*p`?**
`p` = the address stored in the pointer.
`*p` = the value at that address (dereferencing).

**Q: Why did insertAtTail crash?**
`Node* temp;` was declared but never initialized — wild pointer.
`temp->link` tried to dereference a garbage address = undefined behavior.
Fix: `temp = head;`

### Complexity Drill
```
for(int i = 0; i < n; i++)
    for(int j = i; j < n; j++)
        // O(1)

i=0 → n operations
i=1 → n-1 operations
...
i=n-1 → 1 operation

Sum = n + (n-1) + ... + 1 = n(n+1)/2 = O(n²)
```
**Correction:** Write exact counts before applying Big-O. Big-O wraps the final bound, not intermediate terms.

---

## Day 2 — March 15, 2026
### Topic: C String Functions from Scratch

---

### my_strlen

**Final implementation:**
```c
int my_strlen(char* v){
    int counter = 0;
    while((*v) != '\0'){
        counter++;
        v += 1;
    }
    return counter;
}
```

**Attempt 1 — what I tried:**
```c
while((*v) = '\0')
```
**What went wrong:** Used `=` (assignment) instead of `==` (comparison). Assigned `'\0'` to `*v`, which evaluates to 0 (false) — loop never executed. Also had redundant null check before the loop.

**Key concept:** `'\0'` is ASCII value 0, not a null pointer. Loop until null terminator — it marks the end of every C string.

---

### my_strcpy

**Final implementation:**
```c
char* my_strcpy(char* dest, char* src){
    int i = 0;
    while(*(src+i) != '\0'){
        *(dest+i) = *(src+i);
        i++;
    }
    *(dest+i) = *(src+i);
    return dest;
}
```

**Attempt 1 — what I tried:**
```c
char* strcpy(char arr1[], char arr2[]){
    int sizeArr1 = sizeof(arr1)/sizeof(arr1[0]);
    int sizeArr2 = sizeof(arr2)/sizeof(arr2[0]);
    ...
}
```
**What went wrong:** Used `sizeof` on array parameter. Arrays decay to pointers when passed to functions — `sizeof(arr1)` gives size of pointer (8 bytes), not array. Size information is lost at the function boundary.
**Memory level:** The function receives only an address, not a copy of the array. There is no size metadata attached.

**Attempt 2 — what I tried:**
```c
while(*arr1 != '\0'){
    arr2[j++] = arr1[i++];
}
```
**What went wrong:** Mixed pointer dereferencing (`*arr1`) with index access (`arr1[i]`). Condition checks `*arr1` but pointer never advances — infinite loop.
**Takeaway:** Never mix indexing and pointer arithmetic in the same operation on the same variable.

**Attempt 3:**
Same mixing mistake with different variable names. Condition `*src` never changes because `src` pointer never moves while using `src[i]` in body.

**Key concept:** Array decay — passing an array to a function loses size information. Always use null terminator or pass size explicitly.

---

### my_strcmp

**Final implementation:**
```c
int my_strcmp(char* str1, char* str2){
    while(*str1 != '\0' && *str2 != '\0'){
        if(*str1 != *str2)
            return *str1 - *str2;
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
```

**Attempt 1 — what I tried:**
```c
else if(*str1 > *str2) return -1;
else return 1;
```
**What went wrong:** Return values were flipped. Returned -1 when str1 > str2 (should be positive). Returned 1 when str1 < str2 (should be negative). Also wrote redundant three-way check at end.

**Why `*str1 - *str2` works:**
- `'\0'` is ASCII 0
- When str1 ends before str2: `0 - ascii_value` = negative ✓
- When str2 ends before str1: `ascii_value - 0` = positive ✓
- When both end together: `0 - 0` = 0 ✓
- The subtraction handles all three cases in one expression

**C standard:** `strcmp` returns negative/zero/positive — magnitude doesn't matter. Raw subtraction is valid and faster than hardcoded -1/0/1.

**Valgrind output:**
```
0       ← "hello" == "hello"
-115    ← "Vampire" < "Vampires"
115     ← "Vampires" > "Vampire"
0       ← "hello" == "hello"
-1      ← "abc" < "abd"
1       ← "abd" > "abc"
-99     ← "ab" < "abc"
```

---

### my_strcat

**Final implementation:**
```c
char* my_strcat(char* dest, char* src){
    char* original = dest;
    while(*dest != '\0') dest++;
    while(*src != '\0'){
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return original;
}
```

**Attempt 1 — what I tried:** Used do-while loop.
**What went wrong:**
- do-while executes body before checking condition
- Empty src string: copies `'\0'` into dest, advances both pointers, THEN checks — already moved one position too far
- Return value was `dest` after advancing — returns pointer to null terminator, not start of string

**Fix:**
- Replace do-while with regular while — handles empty string correctly
- Save original dest pointer before advancing: `char* original = dest;`
- Return `original`, not `dest`

**Key concept:** `'\0'` is a null CHARACTER (ASCII 0), not a null POINTER (`NULL`/`nullptr`). These are completely different things. Confusing them causes bugs in pointer-heavy code.

---

### Day 2 — Most Important Insight
**Uninitialized memory has no guaranteed null terminator.** Passing an uninitialized char array to any string function that loops until `'\0'` will run forever into memory that doesn't belong to you. This is the same root cause as the insertAtTail bug — just a different form.

---

### Valgrind Lesson — Deliberate Buffer Overflow
Deliberately copied 8-byte string into 5-byte buffer.
Valgrind reported:
```
Invalid write of size 1
Address 0x1fff001000 is not stack'd, malloc'd or (recently) free'd
Process terminating with signal 11 (SIGSEGV)
```
**What this means:**
- Valgrind caught the exact line of the invalid write
- Without valgrind: could silently corrupt adjacent stack variables, crash 50 lines later with no obvious cause
- With valgrind: exact file, exact line, exact nature of error

---

## Compilation Errors Encountered

### "undefined reference to main"
**Cause:** No `main()` function in file, or terminal in wrong directory.
**Fix:** Add `main()` or `cd` into correct directory.

### "No such file or directory" from g++
**Cause:** Terminal is in parent directory, not the directory containing the file.
**Fix:** `cd` into the correct subdirectory first.

### Name conflict warnings (strlen, strcpy)
**Cause:** Function names clash with standard library.
**Fix:** Prefix with `my_` — `my_strlen`, `my_strcpy`, etc.

---

## Commands Reference
```bash
# Compile with warnings and debug info
gcc -Wall -Wextra -g -o output_name source.c

# Run under valgrind
valgrind --leak-check=full ./output_name

# Compile with AddressSanitizer
gcc -fsanitize=address -g -o output_name source.c

# Compile with UndefinedBehaviorSanitizer
gcc -fsanitize=undefined -g -o output_name source.c
```
