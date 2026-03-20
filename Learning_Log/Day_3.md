## Day 3 — March 16, 2026
### Topic: Structs, Padding, Memory Layout

### Struct Memory Padding
**Key concept:** The compiler adds unused bytes between the  members of structs or at the end of struct so that it can satisfy the memory allignment requirement for the CPU and RAM.
This is done so that RAM can fetch and the CPU can read the data in a signle operation.

###Struct Padding Experiments:-
**Experiment 1**:-
```c
struct A{char a; int b;};
```

- Prediction: 8bytes
- Actual: 8bytes
- Why: char takes one byte at address 0, then 3bytes of padding is inserted then, int is added at address 4.

**Experiment 2**:- 
```c
struct B{int a; char b; int c; char d;};
```

- Prediction: 16bytes
- Actual: 16bytes
- Why: int takes four and starts at address 0, then at address 4 char takes 1 byte then 3bytes of padding is added.then at address 8 int starts and take 4 bytes then, char takes one byte at address 4 followed by 3 bytes of padding.

**Experiment 3**:-
```c
struct C{int a,b; char c,d;}; 
```

- Prediction: 12bytes
- Actual: 12bytes
- Why: int take four bytes starting from address 0, then starting at address 4 it takes another four bytes, then at address 8 2bytes are reserved for two char varibles, one byte each followed by two bytes of padding.

### Implementations
1. Student struct — array of 5, scanf input, highest scorer finder
2. Point struct — distance calculator using Pythagorean theorem
3. Node struct — two nodes created manually, linked with pointers, traversed and printed

### Conceptual Exit Question Answer
Q: What is struct memory padding? Why does the compiler insert it? What rule determines how much padding?

Ans:-  The compiler adds unused bytes between the  members of structs or at the end of struct so that it can satisfy the memory allignment.
- This is done so that RAM can fetch and the CPU can read the data in a signle operation.
- Memory padding is the unused bytes that are added by the compilers.

The only thumb or rule for deciding how much padding is added:-
1. Each member starts at an address that is a multiple of its own size.
2. Total struct size rounds up to a multiple of the largest member's size. 
### Today's single most important insight

- The lower bits of the adrress never even travel to RAM, only the upper bit are used to fetch the chunk, the lower bits of the address remain with the CPU.
- The RAM returns the chunk whose address CPU provides.
- That's why misaligned access leads to two fetches.
