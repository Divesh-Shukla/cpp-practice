## Day 10 — 25 March, 2026

**Done:**  
Implemented and debugged dynamic memory concepts with hands-on validation using Valgrind:

- malloc/free for single int — verified no leaks  
- malloc/free for array — understood uninitialized memory behavior  
- calloc vs malloc — observed zero-initialization vs garbage  
- realloc — resized memory while preserving data  
- Demonstrated dangling pointer — observed same address, invalid ownership  
- Demonstrated use-after-free — Valgrind invalid read  
- Demonstrated double-free — runtime abort (`tcache` error) + Valgrind detection  
- Demonstrated memory leak — “definitely lost” block  
- Implemented dynamic 2D array (pointer-to-pointer) and freed correctly  
- Built dynamic array struct:
  - create  
  - push (with resizing)  
  - get  
  - destroy  
- Achieved near Valgrind-clean runs (fixed leaks, invalid reads, double frees)

---

**Key concepts:**  

1. **Memory ownership model:**  
   Memory allocated via `malloc` belongs to the program until explicitly freed. After `free`, ownership is returned to the allocator, and the pointer becomes invalid (dangling).

2. **Undefined behavior:**  
   Accessing freed or uninitialized memory leads to undefined behavior — may appear correct, return garbage, or crash.

3. **Heap reuse:**  
   Freed memory is not erased — it is reused. Observed same address reused across allocations.

4. **Valgrind diagnostics:**  
   - invalid read → use-after-free  
   - invalid free → double free  
   - definitely lost → memory leak  

5. **Allocation vs Initialization:**  
   `malloc` allocates raw memory (uninitialized), while `calloc` initializes memory to zero.

---

**Exit Q:**  
*After calling `free(p)`, what is the value of `p`? What happens if you dereference it? What happens if you free it again? Answer at the memory level.*

After calling `free(p)`, the pointer `p` still holds the same address but the memory is returned to the allocator and is no longer owned by the program. Dereferencing `p` results in undefined behavior because the memory may be reused or modified. Freeing `p` again causes a double free, leading to undefined behavior and possible program termination due to heap corruption.

---

**Confusion:**  

- How `realloc` internally manages memory (in-place vs move)  
- When allocator reuses memory vs gives fresh pages  
- Internal structure of heap (free lists, tcache behavior)  
- Difference between “invalid but readable” vs “invalid and crashing” memory  

---