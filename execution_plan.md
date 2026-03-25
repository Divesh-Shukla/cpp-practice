# 4-WEEK EXECUTION PLAN
## C++ & DSA Foundations — Divesh Shukla
### March 14 – April 13, 2026

---

## HOW TO USE THIS DOCUMENT

- Each day has: **Goal → Theory → Implementation → Problems → Conceptual Exit Question**
- The Conceptual Exit Question is non-negotiable. You must answer it without reference before marking the day complete.
- ✅ = completed | 🔄 = in progress | ⏭ = carried forward
- Flexibility rule: if you finish a day's work early, pull the next day forward. Never idle.
- Commit to GitHub every day: `git add . && git commit -m "Day N: summary" && git push origin main`

---

## WEEK 1 — COMPLETED (March 14–15)

### Day 1 — March 14 ✅
**What was done:**
- Environment setup: gcc, g++, gdb, valgrind, make, clang installed and verified
- First valgrind run on LinkedList code — clean output understood
- Pointer baseline written from memory (wild pointer, dereferencing, insertAtTail bug diagnosed)
- Complexity drill: derived O(n²) for nested loop via summation
- insertAtTail bug fixed: `Node* temp = head;`

**Key concept locked:** Uninitialized pointer = wild pointer = undefined behavior. Declaring `Node* temp;` without assigning it gives garbage address. Dereferencing it reads/writes random memory.

---

### Day 2 — March 15 ✅
**What was done:**
- K.N. King Chapter 8 (array decay) and Chapter 13 (null termination) — active reading
- Implemented from scratch: `my_strlen`, `my_strcpy`, `my_strcmp`, `my_strcat`
- All four: compiled with `-Wall -Wextra -g`, tested with edge cases, valgrind clean
- Deliberate buffer overflow — saw valgrind catch `Invalid write of size 1` + SIGSEGV
- Learned: `'\0'` is ASCII 0 (null character), NOT a null pointer

**Key concepts locked:**
- Array decay: array passed to function loses size info, decays to pointer
- Never mix pointer arithmetic and index access on same variable
- `sizeof` on array parameter gives pointer size, not array size
- `*str1 - *str2` works for strcmp because `'\0'` = 0

---

### Day 3 — March 16 ✅
**What was done:**
- K.N. King Chapter 16 — struct memory layout and padding
- Empirically observed padding: `char[29] + int + int` = 40 bytes, not 37
- Implemented: Student struct (array of 5, highest scorer), Point struct (distance calculator), Node struct (manual linking, traversal)
- Discovered `nullptr` is C++, not C — C uses `NULL`
- Sunday Audit completed

**Key concept locked:**
- Padding exists because CPU reads memory in aligned chunks (multiples of 4/8)
- Compiler inserts padding bytes automatically — member order affects total struct size
- Arrow operator `->` = dereference + dot: `ptr->x` is `(*ptr).x`

---

## WEEK 2 — ACTIVE (March 17–22)

### Day 4 — March 17✅
**Goal:** Compilation pipeline — understand how code becomes an executable

**Theory (30 min):**
- K.N. King Chapter 15 (Writing Large Programs) — full chapter
- Focus: header files vs source files, include guards, declaration vs definition, translation units

**Implementation (60 min):**

Build this exact 3-file project from scratch:

*mathutils.h*
```c
#ifndef MATHUTILS_H
#define MATHUTILS_H
int add(int a, int b);
int multiply(int a, int b);
float average(int* arr, int n);
#endif
```

*mathutils.c* — implement all three functions

*main.c* — call all three, print results

Compile manually (NOT with one command):
```bash
gcc -c mathutils.c -o mathutils.o
gcc -c main.c -o main.o
gcc mathutils.o main.o -o app
./app
```

Then break it deliberately:
1. Remove definition of `add()` from mathutils.c → compile → read linker error
2. Include mathutils.h twice without include guard → compile → observe
3. Fix both

**Problems (30 min):**
1. Add a fourth function `isPrime(int n)` — declare in header, define in separate file, call from main
2. Move `main()` into a third file `runner.c` — compile all three separately, link manually

**Conceptual Exit Question:**
*In one sentence each: what does the compiler do? What does the linker do? Why are they separate steps?*
Write your answer before closing today. No reference.

---

### Day 5 — March 18✅
**Goal:** Makefile + gdb — automate builds, debug without printf

**Theory (20 min):**
- GNU Make Manual Chapters 2–3 (targets, dependencies, variables, phony targets)
- GDB docs: "A Sample GDB Session" — read once, implement immediately

**Implementation (70 min):**

Task 1 — Write Makefile for Day 4 project:
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g

app: main.o mathutils.o
	$(CC) main.o mathutils.o -o app

main.o: main.c mathutils.h
	$(CC) $(CFLAGS) -c main.c

mathutils.o: mathutils.c mathutils.h
	$(CC) $(CFLAGS) -c mathutils.c

clean:
	rm -f *.o app
```
Run: `make` → `make clean` → `make` again. Explain what happened each time.

Task 2 — Use gdb on a deliberate bug:
```c
int divide(int a, int b){ return a/b; }
int main(){
    int x = divide(10, 0);  // division by zero
    printf("%d\n", x);
    return 0;
}
```
```bash
gcc -g -o buggy buggy.c
gdb ./buggy
(gdb) run
(gdb) bt
(gdb) frame 0
(gdb) print a
(gdb) print b
(gdb) quit
```
Read every line of gdb output. Understand what `bt` (backtrace) shows.

Task 3 — Use gdb on your linked list:
Add a deliberate NULL dereference to your linked list code. Use gdb to find exact line.

**Problems (30 min):**
1. Makefile with debug and release targets (debug: `-g -O0`, release: `-O2`)
2. Use gdb to find bug in this recursive function — intentionally broken:
```c
int factorial(int n){
    return n * factorial(n);  // missing base case
}
```
Set breakpoint, step 5 times, read the backtrace when it crashes.

**Conceptual Exit Question:**
*What is a stack frame? When you call `factorial(3)` which calls `factorial(3)` recursively — what does the backtrace show and why does it eventually crash?*

---

### Day 6 — March 19✅
**Goal:** Memory layout — understand what the CPU sees when your program runs

**Theory (30 min):**
- CS:APP Chapter 3.7 — Stack frames (read slowly, draw as you go)
- K.N. King Chapter 18 — scope vs lifetime distinction

**Implementation (60 min):**

For each program below — draw the memory layout (stack/heap/text/data) on PAPER before running. Then run and compare:

```c
// Program 1 — stack variables
int x = 10;
int* p = &x;
*p = 20;
printf("%d\n", x);  // what prints?

// Program 2 — lifetime
void foo(){
    int local = 5;
    printf("%p\n", &local);  // print address
}
int main(){
    foo();
    foo();  // same address or different?
}

// Program 3 — dangling pointer (DO NOT DEREFERENCE — just print address)
int* dangerous(){
    int local = 42;
    return &local;
}
int main(){
    int* p = dangerous();
    printf("%p\n", p);  // address of dead variable
    // printf("%d\n", *p);  // DO NOT — UB
}

// Program 4 — static vs local
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

**Problems (30 min):**
1. Predict the output of Program 4 before running it — write prediction first
2. Write a program that demonstrates a variable living on heap vs stack — allocate same data both ways, print both addresses, observe which range they fall in

**Conceptual Exit Question:**
*A function returns a pointer to a local variable. The caller dereferences it. Describe exactly what has happened in memory between the return and the dereference. Why is the result undefined rather than just wrong?*

---

### Day 7 — March 20✅
**Goal:** Pointer fundamentals — the most important day in Phase 1

**Theory (20 min):**
- K.N. King Chapter 11 (Pointers) — complete
- K.N. King Chapter 12 (Pointers and Arrays) — complete
- Method: read one section, close, write key idea + one code snippet from memory, check

**Implementation (90 min) — 15 small programs, one concept each:**
```
1.  Declare int*, assign address, dereference, modify original
2.  Print p (the address) and *p (the value) — observe format
3.  Show &x gives same address as p after p = &x
4.  Pointer to pointer (int**) — declare, assign, double-dereference
5.  nullptr/NULL check before dereferencing
6.  Pointer comparison (p1 == p2)
7.  sizeof(pointer) vs sizeof(*pointer) — observe on your machine
8.  const int* p — pointer to const (can't modify value)
9.  int* const p — const pointer (can't modify address)
10. const int* const p — both const
11. Pointer as function parameter — swap two integers
12. Function returning pointer — safe version (heap allocated)
13. Function returning pointer — dangerous version (stack local)
14. Pointer to struct — dot vs arrow, show they are equivalent
15. Array name as pointer — show arr[i] == *(arr+i)
```
Each: compile `-Wall -Wextra`, fix every warning before next program.

**Problems (20 min):**
1. Implement `void swap(int* a, int* b)` — test it
2. Write a function that takes `int**` and allocates an integer through it

**Conceptual Exit Question:**
*What is the difference between `const int* p` and `int* const p`? Draw what each one looks like in memory — which part is const, the pointer or the value?*

---

### Day 8 — March 21✅
**Goal:** Pointer arithmetic — the mechanism behind array traversal

**Theory (10 min):**
- K.N. King Chapter 12 — pointer arithmetic sections only

**Implementation (80 min):**
```
1.  Array traversal using p++ (no index variable)
2.  Prove arr[i] == *(arr+i) for 5 elements — print both, compare
3.  Pointer difference: p2 - p1 gives element count, not byte count
4.  Implement strlen using pointer arithmetic ONLY (no counter variable, no index)
5.  Implement array copy using pointer arithmetic only
6.  2D array: int arr[3][4] — print address of each row, observe stride
7.  Show that arr+1 advances by sizeof(element) bytes — verify with printf
8.  Pointer past end of array — p = arr + n (valid address, never dereference)
```

**Problems (30 min):**
1. Implement `int* find(int* arr, int n, int target)` — returns pointer to element or NULL
2. Implement `void reverse_array(int* arr, int n)` — using pointer arithmetic, no index

**Conceptual Exit Question:**
*When you write `p++` on an `int*`, how many bytes does the address actually advance? Why? What if it were a `double*`?*

---

### Day 9 — March 22 — DSA Catch-up + Review✅
**Goal:** Begin DSA drills + review pointer fundamentals

**DSA (60 min) — Unit 0.1 Complexity Analysis:**

Derive complexity for each — write summation, then closed form:
```
1. for(i=0; i<n; i++) for(j=0; j<i; j++) → O(?)
2. for(i=1; i<=n; i*=2) → O(?)
3. for(i=n; i>0; i/=2) → O(?)
4. Recursive: T(n) = T(n/2) + O(1) → O(?) [Master theorem]
5. Recursive: T(n) = 2T(n/2) + O(n) → O(?) [Master theorem]
6. Dynamic array push_back amortized — explain why O(1) amortized despite occasional O(n)
7. Hash table insert — O(1) average, O(n) worst — explain when worst case occurs
```

**Review (30 min):**
Implement from memory — no reference, no notes:
1. `my_strlen` — 3 minutes max
2. `swap(int* a, int* b)` — 2 minutes max
3. Array traversal using pointer arithmetic — 3 minutes max

If any takes longer than the time limit — that concept needs more practice.

**Conceptual Exit Question:**
*What is amortized O(1)? Why is dynamic array push_back O(1) amortized even though it occasionally copies the entire array?*

---

## WEEK 3 — PLANNED (March 23–29)

### Day 10 — March 23
**Goal:** Dynamic memory — malloc, free, heap allocation

**Theory (20 min):**
- K.N. King Chapter 17 — dynamic memory sections
- Focus: malloc vs calloc, what free actually does, what dangling pointer means post-free

**Implementation (80 min):**
```
1.  malloc/free for single int — valgrind clean
2.  malloc/free for array of 10 ints — valgrind clean
3.  calloc vs malloc — print uninitialized malloc vs zeroed calloc
4.  realloc to double array size — preserve existing elements
5.  Demonstrate dangling pointer: free(p), then print p (address, not value)
6.  Demonstrate double-free — run under valgrind, read the error
7.  Dynamic 2D array: allocate array of int pointers, each pointing to row
8.  Use the 2D array
9.  Free 2D array correctly: loop to free each row, then free pointer array
10. Implement dynamic array struct:
    struct DynArray { int* data; int size; int capacity; };
    - create(int capacity)
    - push(DynArray* arr, int val) — double capacity when full
    - get(DynArray* arr, int i)
    - destroy(DynArray* arr)
    Valgrind: zero errors, zero leaks
```

**Problems (20 min):**
1. Write a function that allocates and returns a copy of an array — caller must free
2. Demonstrate what valgrind reports for: use-after-free, double-free, memory leak (three separate programs)

**Conceptual Exit Question:**
*After calling `free(p)`, what is the value of `p`? What happens if you dereference it? What happens if you free it again? Answer at the memory level.*

---

### Day 11 — March 24
**Goal:** Const correctness + Undefined Behavior

**Theory (20 min):**
- "What Every C Programmer Should Know About Undefined Behavior" — Chris Lattner (find online)
- Focus: why UB is worse than "just wrong" — compiler optimization implications

**Implementation (60 min):**

Const correctness:
```
1.  const int* p — modify through p (compiler error — expected)
2.  int* const p — modify p itself (compiler error — expected)
3.  Pass string to function as const char* — correct signature
4.  Implement const-correct my_strlen: int my_strlen(const char* s)
5.  Implement const-correct my_strcmp: int my_strcmp(const char* a, const char* b)
```

UB with sanitizers:
```bash
# Compile with AddressSanitizer
gcc -fsanitize=address -g -o program program.c

# Compile with UBSanitizer  
gcc -fsanitize=undefined -g -o program program.c
```

Trigger and catch each:
```
6.  Null pointer dereference → catch with ASan
7.  Out-of-bounds array access → catch with ASan
8.  Use-after-free → catch with ASan
9.  Signed integer overflow: INT_MAX + 1 → catch with UBSan
10. Uninitialized variable read → catch with UBSan
```

**Problems (20 min):**
1. Take your string functions from Day 2 — make all parameters const-correct
2. Write a program with 3 UB bugs — run without sanitizers (may work), then with sanitizers (caught)

**Conceptual Exit Question:**
*Why can undefined behavior cause a program to appear to work correctly in debug mode but crash in release mode? What is the compiler doing differently?*

---

### Day 12 — March 25
**Goal:** Binary Search — master the pattern, not just the algorithm

**Theory (15 min):**
- CLRS Chapter 2.3 — binary search
- Focus: loop invariant — what is true at the start of every iteration?

**Implementation (45 min):**
```
1.  Iterative binary search — standard
2.  Recursive binary search
3.  Find FIRST occurrence in array with duplicates
4.  Find LAST occurrence in array with duplicates
5.  Find floor (largest element ≤ target)
6.  Find ceiling (smallest element ≥ target)
7.  Implement lower_bound from scratch
8.  Implement upper_bound from scratch
```

**LeetCode Problems (60 min):**
- LC 704 — Binary Search (warm-up, 5 min)
- LC 33 — Search in Rotated Sorted Array
- LC 153 — Find Minimum in Rotated Sorted Array
- LC 69 — Sqrt(x) using binary search
- LC 875 — Koko Eating Bananas (binary search on answer)

**Conceptual Exit Question:**
*What is the loop invariant in binary search? Why does `mid = left + (right-left)/2` instead of `(left+right)/2` matter? When does the second form overflow?*

---

### Day 13 — March 26
**Goal:** C++ transition — C++ I/O, references, type system

**Theory (20 min):**
- A Tour of C++ Chapter 1 — read actively
- C++ Primer Chapter 2.3, 6.2 — references

**Implementation (70 min):**
```
1.  Hello world in C++ — cout, cin, namespace std
2.  Convert your my_strlen from C to C++ — use std::string
3.  Read integers until EOF — cin >> n in while loop
4.  Demonstrate auto type deduction — 5 examples
5.  Range-based for loop on array and vector
6.  Reference declaration — int& ref = x
7.  Swap using references (not pointers)
8.  Pass large struct by const reference — measure vs pass by value
9.  Demonstrate dangling reference: return reference to local variable
10. Pass by value vs pass by reference vs pass by const reference — three versions of same function
```

**Problems (30 min):**
1. Implement matrix addition using const reference parameters
2. Write a function that takes `string&` and reverses it in place

**Conceptual Exit Question:**
*What are three things a reference can't do that a pointer can? What is one thing a reference guarantees that a pointer doesn't? Which should you prefer in C++ and why?*

---

### Day 14 — March 27
**Goal:** C++ new/delete + exception basics

**Theory (15 min):**
- C++ Primer Chapter 12.1 — new/delete
- A Tour of C++ Chapter 3.5 — exception handling

**Implementation (75 min):**

new/delete:
```
1.  Allocate int with new, delete — valgrind clean
2.  Allocate array with new[], delete[] — valgrind clean
3.  Show new calls constructor: create test class with print in constructor/destructor
4.  Use nullptr instead of NULL — demonstrate nullptr is type-safe
5.  Allocate 2D array with new — array of pointers to arrays
6.  Free 2D array correctly with nested delete[]
7.  Convert your C DynArray struct to use new/delete instead of malloc/free
```

Exception handling:
```
8.  throw and catch std::exception
9.  Throw custom exception (derive from std::exception, override what())
10. Demonstrate stack unwinding — local objects destroyed during exception
11. Catch by const reference (correct) vs catch by value (incorrect — slicing)
12. Mark function noexcept — observe compiler behavior
```

**Problems (20 min):**
1. Implement exception-safe dynamic array: if allocation fails, no leak
2. Convert error-code style C function to exception-throwing C++ function

**Conceptual Exit Question:**
*Why does `new` call constructors but `malloc` doesn't? Why does this matter? What is object slicing in exception handling and how do you prevent it?*

---

### Day 15 — March 28
**Goal:** DSA — Binary search problems + prefix sums

**Full DSA day — no C++ theory today**

**Prefix Sum Implementation (30 min):**
```
1.  Build prefix sum array from input
2.  Range sum query using prefix array: sum(l,r) = prefix[r] - prefix[l-1]
3.  2D prefix sum array
4.  Difference array for range updates
```

**LeetCode Problems (90 min):**
- LC 303 — Range Sum Query Immutable
- LC 304 — Range Sum Query 2D Immutable
- LC 560 — Subarray Sum Equals K (prefix sum + hash)
- LC 162 — Find Peak Element
- LC 410 — Split Array Largest Sum (binary search on answer — hard)

**Complexity drill:**
For each problem you solve today — write the time and space complexity before submitting. If your first solution is O(n²), find the O(n) solution before moving on.

**Conceptual Exit Question:**
*Why does `sum(l, r) = prefix[r] - prefix[l-1]` work? Derive it from first principles. What is the edge case when l=0 and how do you handle it?*

---

### Day 16 — March 29
**Goal:** Review + catch-up + GitHub push

**Morning (45 min) — Retrieval practice:**
Implement from memory, no reference, timed:
1. Binary search with correct invariant — 4 minutes
2. my_strlen — 2 minutes
3. Dynamic array push with realloc — 8 minutes
4. Pointer swap — 2 minutes

If any fails the time limit — add to next week's review list.

**Afternoon (45 min) — Weak point targeting:**
Look at your implementations from this week. Find the one that took the most attempts or felt least solid. Reimplement it from scratch.

**GitHub:**
```bash
git add .
git commit -m "Week 2-3: Compilation, gdb, memory layout, pointers, C++ transition"
git push origin main
```

**Weekly Audit:**
1. What did I complete vs planned?
2. Which concept felt shakiest?
3. What is the one thing I must not carry forward unresolved?

---

## WEEK 4 — PLANNED (March 30 – April 5)

### Day 17 — March 30
**Goal:** C++ Classes — encapsulation done right

**Theory (15 min):**
- C++ Primer Chapter 7 — classes
- Focus: const member functions, this pointer, when struct vs class

**Implementation (75 min):**
```
1.  Rectangle class — width, height, area(), perimeter(), all const-correct
2.  BankAccount class — private balance, deposit(), withdraw() with validation
3.  Demonstrate this pointer — method chaining using return *this
4.  Compare struct vs class: only difference is default access specifier
5.  Const member function: int getX() const — cannot modify members
6.  Non-const member function: void setX(int x) — can modify
7.  Private helper method — used internally, not exposed
8.  Static member variable — shared across all instances
```

**Problems (30 min):**
1. Implement Complex class — real, imag, add(), subtract(), print()
2. Implement Date class — day, month, year, isValid(), compare()

**Conceptual Exit Question:**
*What does `const` mean at the end of a member function declaration? What does the compiler prevent you from doing inside that function? Why is this important for correctness?*

---

### Day 18 — March 31
**Goal:** Constructors & Destructors — initialization done right

**Theory (15 min):**
- C++ Primer Chapter 7.1, 7.5
- Effective C++ Items 4, 5, 6

**Implementation (75 min):**
```
1.  Default constructor vs parameterized constructor
2.  Initialization list — int x; MyClass(): x(5) {} vs body assignment
3.  Demonstrate initialization order: base members, then body
4.  Destructor — print when called, observe order
5.  Delegating constructor (C++11) — one constructor calls another
6.  explicit keyword — prevent implicit conversion
7.  Demonstrate implicit conversion problem (no explicit)
8.  RAII file handle: open in constructor, close in destructor
9.  const member initialization — must use initialization list
10. Reference member initialization — must use initialization list
```

**Problems (30 min):**
1. Implement RAII lock guard — lock in constructor, unlock in destructor
2. Debug this: member used before initialized (initialization order bug)

**Conceptual Exit Question:**
*Why must const members and reference members be initialized in the initialization list and not in the constructor body? What has already happened by the time the constructor body runs?*

---

### Day 19 — April 1
**Goal:** Copy semantics — the most critical C++ unit

**Theory (20 min):**
- C++ Primer Chapter 13.1
- Effective C++ Items 10, 11, 12
- Rule of Three: if you write any one of {destructor, copy constructor, copy assignment}, you must write all three

**Implementation (90 min) — do not rush this:**
```
1.  Demonstrate shallow copy problem:
    - Class with int* data
    - Default copy → two objects share same pointer
    - First destructor frees memory
    - Second destructor: double-free → valgrind catches it

2.  Implement deep copy constructor:
    MyClass(const MyClass& other){
        data = new int(*other.data);  // allocate new, copy value
    }

3.  Implement copy assignment operator:
    MyClass& operator=(const MyClass& other){ ... }

4.  Self-assignment check:
    if(this == &other) return *this;

5.  Copy-and-swap idiom — exception-safe assignment

6.  Delete copy operations for non-copyable class:
    MyClass(const MyClass&) = delete;
    MyClass& operator=(const MyClass&) = delete;

7.  Implement Rule of Three for String class (char* buffer):
    - Constructor
    - Destructor
    - Copy constructor (deep copy)
    - Copy assignment (deep copy + self-assignment check)
    Valgrind: ZERO errors before moving on
```

**Conceptual Exit Question:**
*What is the Rule of Three? Why does implementing a destructor imply you need a copy constructor and copy assignment operator? What goes wrong if you implement the destructor but rely on compiler-generated copy operations?*

---

### Day 20 — April 2
**Goal:** Operator overloading

**Theory (10 min):**
- C++ Primer Chapter 14
- Key rule: member vs non-member — stream operators must be non-member

**Implementation (70 min):**
```
Build on your Complex class from Day 17:
1.  operator+ (returns new Complex)
2.  operator+= (modifies and returns *this)
3.  operator== and operator!=
4.  operator< (for sorting)
5.  operator<< for ostream (non-member, friend)
6.  operator>> for istream (non-member, friend)
7.  operator[] for array class (return reference)
8.  Prefix ++ vs postfix ++ (postfix takes dummy int parameter)
```

**Problems (30 min):**
1. Implement Matrix class with operator+, operator*, operator[], operator<<
2. Implement Fraction class with all arithmetic operators, reduce on construction

**Conceptual Exit Question:**
*Why must `operator<<` be a non-member function? What does `friend` do when applied to it? What is the difference between returning by value and returning by reference from an operator, and when do you use each?*

---

### Day 21 — April 3
**Goal:** DSA — Two Pointers pattern

**Full DSA day**

**Theory (15 min):**
- Read: "Two Pointers Technique" — understand the invariant before touching problems
- Key insight: two pointers reduce O(n²) nested loop to O(n) by maintaining a sorted/ordered invariant

**LeetCode Problems (105 min) — in order, do not skip:**
- LC 167 — Two Sum II (sorted array) — warm-up
- LC 26 — Remove Duplicates from Sorted Array
- LC 27 — Remove Element
- LC 283 — Move Zeroes
- LC 11 — Container With Most Water
- LC 15 — 3Sum
- LC 75 — Sort Colors (Dutch National Flag)
- LC 42 — Trapping Rain Water

**For each problem:**
1. Before coding: write the invariant you'll maintain
2. After solving: write time and space complexity
3. If O(n²) — find O(n) solution before moving on

**Conceptual Exit Question:**
*What is the invariant in the two-pointer approach for Container With Most Water? Why do you always move the pointer pointing to the shorter line?*

---

### Day 22 — April 4
**Goal:** Inheritance & Polymorphism

**Theory (20 min):**
- C++ Primer Chapter 15
- Effective C++ Items 7, 34, 36
- Critical rule: base class destructor must be virtual

**Implementation (70 min):**
```
1.  Shape base class — virtual area(), virtual perimeter()
2.  Circle derives from Shape — override area(), perimeter()
3.  Rectangle derives from Shape
4.  Polymorphism: Shape* array → call area() on each → correct derived version called
5.  Demonstrate virtual destructor necessity:
    Shape* s = new Circle();
    delete s;  // without virtual destructor: Circle destructor never called → leak
6.  Pure virtual function — abstract class, cannot instantiate
7.  override keyword (C++11) — compiler verifies you're actually overriding
8.  Demonstrate slicing: pass Circle by value to function expecting Shape
9.  vtable: explain why virtual function calls are slightly slower
10. dynamic_cast: safe downcast from Shape* to Circle*
```

**Problems (30 min):**
1. Implement Animal hierarchy — Animal, Dog, Cat — polymorphic speak()
2. Debug memory leak from missing virtual destructor — find with valgrind

**Conceptual Exit Question:**
*What is object slicing? When does it happen? Why does passing a derived object by value to a base class function lose the derived behavior? How do you prevent it?*

---

### Day 23 — April 5
**Goal:** DSA — Sliding Window pattern

**Full DSA day**

**Theory (15 min):**
- Key insight: sliding window maintains a window with a valid property
- Fixed window vs variable window — know when to use each
- Window invariant: define what makes a window valid before coding

**LeetCode Problems (105 min) — in order:**
- LC 643 — Maximum Average Subarray I (fixed window — warm-up)
- LC 3 — Longest Substring Without Repeating Characters (variable window)
- LC 209 — Minimum Size Subarray Sum (variable window)
- LC 424 — Longest Repeating Character Replacement
- LC 567 — Permutation in String
- LC 438 — Find All Anagrams in String
- LC 76 — Minimum Window Substring (hard — attempt, don't skip)

**For each problem:**
1. Write the window invariant before coding
2. Identify: fixed or variable window?
3. Write complexity after solving

**Conceptual Exit Question:**
*What is the difference between a fixed window and a variable window? In the variable window, when do you expand and when do you shrink? Write the general template.*

---

## WEEK 5 — PLANNED (April 6–13)

### Day 24 — April 6
**Goal:** STL Containers — minimum viable subset for DSA

**Theory (15 min):**
- C++ Primer Chapter 9 (vector, deque), Chapter 11 (unordered containers)
- Focus: when to use which container, performance characteristics

**Implementation (60 min):**
```
1.  vector: push_back, insert, erase, iterate — observe reallocation
2.  Demonstrate iterator invalidation: erase in loop (wrong vs correct)
3.  unordered_map: insert, find, erase, iterate
4.  unordered_set: O(1) membership test
5.  stack (adapter over deque): push, pop, top
6.  queue (adapter over deque): push, pop, front
7.  priority_queue: max-heap by default, min-heap with comparator
8.  emplace_back vs push_back — when does it matter?
```

**LeetCode (45 min):**
- LC 1 — Two Sum (unordered_map)
- LC 217 — Contains Duplicate (unordered_set)
- LC 347 — Top K Frequent Elements (unordered_map + priority_queue)

**Conceptual Exit Question:**
*What is iterator invalidation? When does it happen with vector? Write a code example that triggers it and explain what goes wrong at the memory level.*

---

### Day 25 — April 7
**Goal:** Hashing techniques — complement pattern, prefix sum + hash

**Full DSA day**

**Theory (15 min):**
- CLRS Chapter 11 — hash tables (conceptual: collision handling, load factor)
- Complement pattern: instead of nested loop, store seen values and look up complement

**LeetCode Problems (105 min):**
- LC 1 — Two Sum (revisit — implement with complement pattern, explain why O(n))
- LC 128 — Longest Consecutive Sequence
- LC 560 — Subarray Sum Equals K (prefix sum + hash)
- LC 523 — Continuous Subarray Sum
- LC 974 — Subarray Sums Divisible by K
- LC 36 — Valid Sudoku
- LC 380 — Insert Delete GetRandom O(1) (design problem)
- LC 146 — LRU Cache (hash + doubly linked list — hard, attempt)

**Conceptual Exit Question:**
*Why does the complement pattern work for Two Sum? Prove that the hash map approach is O(n) and not O(n²). What is the worst-case complexity of unordered_map lookup and when does it occur?*

---

### Day 26 — April 8
**Goal:** Linked List — problem solving mode

**Full DSA day — your implementation is solid, train the problem-solving speed**

**Warm-up (15 min):**
Implement iterative linked list reverse from memory. Target: under 3 minutes. If over — practice until under.

**LeetCode Problems (105 min):**
- LC 206 — Reverse Linked List (iterative AND recursive)
- LC 21 — Merge Two Sorted Lists
- LC 19 — Remove Nth Node From End
- LC 876 — Middle of Linked List
- LC 141 — Linked List Cycle (Floyd's algorithm)
- LC 142 — Linked List Cycle II (find cycle start)
- LC 234 — Palindrome Linked List
- LC 143 — Reorder List
- LC 23 — Merge K Sorted Lists (hard — uses heap)

**Conceptual Exit Question:**
*In Floyd's cycle detection, why do the fast and slow pointers meet inside the cycle? Prove mathematically that they must meet. Why does starting slow from head and fast from meeting point find the cycle start?*

---

### Day 27 — April 9
**Goal:** Array manipulation patterns

**Full DSA day**

**LeetCode Problems (120 min):**
- LC 53 — Maximum Subarray (Kadane's — derive the algorithm, don't memorize)
- LC 238 — Product of Array Except Self (no division)
- LC 189 — Rotate Array
- LC 121 — Best Time to Buy and Sell Stock
- LC 55 — Jump Game
- LC 56 — Merge Intervals
- LC 48 — Rotate Image (in-place matrix rotation)
- LC 54 — Spiral Matrix

**For Kadane's specifically:**
Before looking up the algorithm — try to derive it yourself from the subproblem: "what is the maximum subarray ending at index i?"

**Conceptual Exit Question:**
*What is the invariant in Kadane's algorithm? Define `dp[i]` as the maximum subarray sum ending at index i. Write the recurrence relation. Why is the answer `max(dp[0], dp[1], ..., dp[n-1])` and not just `dp[n-1]`?*

---

### Day 28 — April 10
**Goal:** Stack applications — monotonic stack

**Full DSA day**

**Theory (15 min):**
- Monotonic stack insight: maintains elements in sorted order, processes "next greater/smaller" in O(n)
- Key: when you pop an element, you've found its answer

**LeetCode Problems (105 min):**
- LC 20 — Valid Parentheses (warm-up)
- LC 155 — Min Stack
- LC 739 — Daily Temperatures (monotonic stack)
- LC 496 — Next Greater Element I
- LC 503 — Next Greater Element II (circular)
- LC 84 — Largest Rectangle in Histogram (hard — the exit criterion)
- LC 42 — Trapping Rain Water (stack approach)
- LC 394 — Decode String

**Conceptual Exit Question:**
*Explain the monotonic stack invariant in Largest Rectangle in Histogram. When you pop a bar from the stack, what have you determined? Why is the width calculation `i - stack.top() - 1`?*

---

### Day 29 — April 11
**Goal:** Queue & Deque applications

**DSA day + C++ review**

**LeetCode Problems (90 min):**
- LC 232 — Implement Queue using Stacks
- LC 225 — Implement Stack using Queues
- LC 622 — Design Circular Queue
- LC 239 — Sliding Window Maximum (deque — O(n))
- LC 862 — Shortest Subarray with Sum at Least K (deque + prefix sum)

**C++ Review (30 min):**
Pick whichever C++ concept felt weakest this week. Reimplement its core exercise from scratch without reference.

**Conceptual Exit Question:**
*In Sliding Window Maximum with deque — what invariant does the deque maintain? Why do you remove elements from the front AND the back? Trace through the first 5 elements of [3,1,3,4,2] with k=3.*

---

### Day 30 — April 12
**Goal:** Full review + Phase assessment

**Morning — Timed implementations (60 min):**
All from memory, timed:
1. Binary search — 4 min
2. Linked list reverse — 3 min
3. Two sum with hash map — 5 min
4. Valid parentheses — 5 min
5. Merge two sorted lists — 7 min
6. Sliding window max subarray sum — 10 min

Record time for each. Any over limit = add to review backlog.

**Afternoon — Mixed problem set (60 min):**
Solve these WITHOUT being told which pattern to use. Identify the pattern yourself first:
- LC 424 — Longest Repeating Character Replacement
- LC 143 — Reorder List
- LC 347 — Top K Frequent Elements

**Conceptual Exit Question:**
*For each of the three problems above — before looking at your solution — write: what pattern did you use and why? What was the key insight that unlocked the solution?*

---

### Day 31 — April 13
**Goal:** GitHub audit + plan forward

**Audit (30 min):**
1. Count total LeetCode problems solved — target was 60–70
2. List every concept that still feels shaky
3. Identify which triage document items are complete vs in-progress

**GitHub cleanup (20 min):**
```bash
git add .
git commit -m "Phase 1 complete: Pre-C++, C++ Modules 1-2, DSA Layers 0-2"
git push origin main
```

**Forward planning (30 min):**
Write your own plan for the next 2 weeks using the planning principles from this document:
1. Count your hours
2. Map dependencies
3. Set phase exit criteria
4. Build in slack

This is the test of whether you can plan independently. Write it, share it, get feedback.

---

## QUICK REFERENCE

### Daily Session Structure (2.5 hrs)
```
[15 min] Retrieval warm-up — write yesterday's key concept from memory
[60 min] Concept + implementation — close-recall-check method
[60 min] Problems — always write complexity before and after
[15 min] Conceptual exit question — no reference, write answer before closing
```

### Minimum Viable Day (2 hrs, bad day)
```
[30 min] Implement one thing from memory
[30 min] Solve one LeetCode problem
[10 min] Write conceptual exit question answer
```

### Sunday Audit (every Sunday, 20 min)
```
1. What did I complete vs planned?
2. Was the gap from time, difficulty, or unclear concept?
3. What adjusts for next week?
```

### Valgrind Commands
```bash
valgrind --leak-check=full ./program
gcc -fsanitize=address -g -o program source.c
gcc -fsanitize=undefined -g -o program source.c
```

### Git Daily Commit
```bash
git add .
git commit -m "Day N: one line summary"
git push origin main
```

### Phase Exit Criteria
**Phase 1 complete when:**
- Dynamic array in C with malloc/free — zero valgrind errors
- Binary search from memory in under 4 minutes
- Rule of Three for any class with dynamic memory — zero valgrind errors
- 60+ LeetCode problems solved

---

*Plan built: March 16, 2026*
*Deadline: May 31, 2026*
*Daily commitment: 2–3 hours*
*Flexibility rule: finish early → pull next day forward. Never idle.*
