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
