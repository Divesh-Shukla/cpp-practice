## Day 8 — March 23, 2026

**Done:**
- Array traversal using `p++` — no index variable
- Proved `arr[i] == *(arr+i)` for all elements
- Pointer difference `p2 - p1` gives element count, not bytes
- Array copy using pointer arithmetic only (`*(brr+i) = *(arr+i)`)
- 2D array row addresses — observed stride = row size in bytes
- Proved `arr+1` advances by `sizeof(int)` = 4 bytes using `char*` cast
- One-past-the-end pointer `arr+n` used as loop boundary — never dereferenced

**Key concept:** Pointer arithmetic is type-aware — `p+1` advances by `sizeof(type)` bytes, not 1. A 2D array is a flat block of memory; rows are contiguous chunks, each separated by `columns × sizeof(element)` bytes (the stride).

**Exit Q:** *When you write `p++` on an `int*`, how many bytes does the address actually advance? Why? What if it were a `double*`?*

`p++` on an `int*` advances 4 bytes — `sizeof(int)`. Pointer arithmetic scales by the size of the pointed-to type so that `p+1` always lands on the next element, not the next byte. For a `double*` it would advance 8 bytes — `sizeof(double)`.

**Confusion:** Why casting to `char*` is needed to get byte-level pointer difference — understood after explanation: `int*` subtraction gives element count, `char*` subtraction gives byte count because `sizeof(char) == 1`.