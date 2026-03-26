## Single Block Dynamic Array — Debugging Log

I have attempted to make single block dynamic array. 

I have coded two versions:
- The first version is the one with a lot of bugs and UB issues.
- The second is the refinement after knowing and understanding all the bugs in the first attempt!

---

## Bugs in Attempt 1

### Bug 1 in the definition of create function!
- Missing return value in `create()` function! The function never returns the address of the allocated memory!
- This in turn leads to the caller (`main`) receiving a garbage pointer.
- Any use of that pointer is undefined behaviour!
- The program can crash, or may even behave randomly!

*If a function is allocating any kind of memory on heap then it must return a valid pointer! Otherwise every operation that depends on the function return would be operating on invalid memory!*

#### Behaviour of program even after bug!
- The program behaved normally due to luck!

---

### Bug 2 in the resizing in push!

- My push function has two parameters:
  1. Pointer to the dynArray
  2. The value to be pushed

- The bug is caused by handing a local pointer the ownership of the reallocated block.
- A local temporary pointer to dynArray was created and the pointer returned by `realloc` was stored in the temp variable.
- Instead of updating the pointer in `main`, I updated only the local pointer.
- Caller still holds the pointer to the old heap memory. This may lead to using a dangling pointer.
- The second bug was not understanding the level of pointer required in the parameter of the push function.

- The push parameter should have been a **double pointer (`dynArray**`)** that receives the address of the pointer from `main`.

#### Effects
- Loss of the original heap block in case `realloc` changes the pointer.
- Caller continues using invalid or outdated pointer.
- Leads to undefined behaviour.

#### Concept gap
- Difference between pointer to data (`dynArray*`) and pointer to pointer (`dynArray**`).
- Pointer ownership and how ownership changes with reallocation.

- Double pointer is used when we might need to change where a pointer points to.
- This is where multiple level pointers come into play.

---

### Bug 3 not updating the capacity after resizing

- I never updated the capacity of the array after resizing.
- I passed capacity = 1 in the main. Even after resizing the memory, the capacity remained unchanged.

#### Effects
- Logical capacity remained fixed while actual memory increased.
- Program assumed capacity was still small while writing beyond it.

---

### Bug 4 Out of Bounds Write

- Even though the capacity never increased logically, the size kept increasing.
- This meant I kept writing beyond the allocated bounds.

#### Effects
- Writing outside allocated memory.
- Memory corruption.
- Program appears to work but is incorrect.

---

### Bug 5 wrong arguments passed through the realloc function

- Incorrect pointer was passed to `realloc`.
- Instead of passing the actual heap pointer, I passed the wrong level of pointer.

#### Effects
- Reallocating wrong memory block.
- Can lead to crashes or undefined behaviour.

#### Concept gap
- `realloc` must always receive the pointer returned by `malloc/calloc/realloc`, not the address of the pointer variable.

---

### Bug 6 Wrong bounds check in get function

- The condition I used to check index validity was wrong.

*Condition used:*  
`index < 0 || index > d->capacity`

*Correct condition:*  
`index < 0 || index >= d->size`

- The index must lie in the range of `0 to size-1`, not `capacity`.

#### Effects
- Allowed access to uninitialized or invalid memory.
- Logical error even if memory exists.

---

## Final Note

- Many parts of the program appeared to work even when incorrect.
- This was due to undefined behaviour and heap reuse.

> Correct output does not imply correct program.

---

## Key Learning

- Always return allocated memory from functions.
- Understand pointer levels (`*` vs `**`).
- `realloc` may change the pointer — must update it correctly.
- Always maintain correct `size` and `capacity`.
- Never write beyond bounds.
- Validate indices using `size`, not `capacity`.