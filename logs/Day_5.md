# Learning Log — C++ & DSA Journey

---

## Day 5 — March 18, 2026
### Topic: Makefile + gdb

---

## Retrieval Warm-Up

**Q1. What are the four stages of compilation, in order?**

1. **Preprocessing** — The source file is passed through the preprocessor, which performs text substitution: macros are expanded and `#include` directives are replaced with the full contents of the referenced file. The output is called a *translation unit* (`.i` file) — the actual unit of compilation.

2. **Compilation** — The translation unit is passed to the compiler, which checks for type mismatches, function signature mismatches, and syntactic validity. If the code violates any C/C++ rules, the compiler throws an error. If it passes, the compiler translates the code into assembly language (`.s` file).

3. **Assembly** — The `.s` file is passed to the assembler, which converts assembly into machine instructions. The output is an *object file* (`.o`). An object file contains machine instructions, a symbol table, metadata, and relocation information. It is not yet executable.

4. **Linking** — The linker takes one or more object files and resolves all undefined references (`U`) by finding matching definitions (`T`) across the object files. If a matching definition is missing, the linker throws an error. If two matching definitions exist for the same symbol, the linker also throws an error. Once all references are resolved, symbol names are replaced with memory addresses and the final executable is produced.

---

**Q2. What does a `.o` file contain, and what does the linker do with multiple `.o` files?**

An object file contains:
- Machine instructions for the source code (unlinked)
- A symbol table listing all functions and variables
- Code metadata
- Relocation information for the linker

The linker takes multiple `.o` files, resolves all cross-file undefined references, replaces symbol names with addresses, and produces a single executable.

---

**Q3. Why does removing a function *definition* (not declaration) cause a linker error, not a compiler error?**

The compiler only needs the *declaration* to verify that a function call matches the expected signature. It doesn't need to see the definition — that's not its job. The linker's job is to connect each function call to its definition. When the definition is missing, the linker finds an unresolved `U` with no matching `T` and throws an error.

---

## Key Concepts

### Makefile

**Structure of a rule:**
```makefile
target: dependencies
	command
```
- **target** — the file to produce, or a named command
- **dependencies** — files this target depends on; if any is newer than the target, Make reruns the command
- **command** — must be indented with a **TAB**, not spaces

**Variables** are declared at the top and expanded with `$(VARNAME)`:
```makefile
CC = gcc
CFLAGS         = -Wall -Wextra -g
CFLAGS_DEBUG   = -Wall -Wextra -g -O0
CFLAGS_RELEASE = -Wall -Wextra -O2
```

**Full Makefile written today:**
```makefile
CC = gcc
CFLAGS         = -Wall -Wextra -g
CFLAGS_DEBUG   = -Wall -Wextra -g -O0
CFLAGS_RELEASE = -Wall -Wextra -O2

.PHONY: clean debug release

app: main.o mathutils.o
	$(CC) main.o mathutils.o -o app

main.o: main.c mathutils.h
	$(CC) $(CFLAGS) -c main.c

mathutils.o: mathutils.c mathutils.h
	$(CC) $(CFLAGS) -c mathutils.c

clean:
	rm -f *.o app

debug:
	$(CC) $(CFLAGS_DEBUG) -c main.c -o main.o
	$(CC) $(CFLAGS_DEBUG) -c mathutils.c -o mathutils.o
	$(CC) main.o mathutils.o -o app

release:
	$(CC) $(CFLAGS_RELEASE) -c main.c -o main.o
	$(CC) $(CFLAGS_RELEASE) -c mathutils.c -o mathutils.o
	$(CC) main.o mathutils.o -o app
```

**`.PHONY`** — Make assumes every target is a file. If a file named `clean` exists, `make clean` would do nothing. `.PHONY` tells Make these are named commands, not files — always run them.

**`clean` command:** `rm -f *.o app`
- `rm` — delete files
- `-f` — force: silently do nothing if files don't exist
- `*.o` — all object files in the current directory
- `app` — the executable

**`-g` vs `-O0` vs `-O2`:**
- `-g` — embed debug symbols (line numbers, variable names). Required for gdb.
- `-O0` — zero optimization. Code runs exactly as written. Essential for debugging.
- `-O2` — aggressive optimization. Faster binary, no debug symbols. Used for release builds.

---

### gdb Commands Used Today

| Command | Usage |
|---|---|
| `gdb ./app` | Open program in gdb |
| `run` | Run the program |
| `bt` | Print backtrace — full call stack at point of crash |
| `frame N` | Inspect a specific stack frame by number |
| `print varname` | Inspect the value of a variable in the current frame |
| `break funcname` | Set a breakpoint at a function |
| `step` | Execute one line, stepping into function calls |
| `quit` | Exit gdb |

---

### Stack Frame

A stack frame is the block of memory allocated on the stack for a single function call. It stores:
- The function's **arguments**
- The function's **local variables**
- The **return address** — where execution should resume after the function returns

Stack frames are pushed on function call and popped (freed) on function return. The stack is a fixed-size memory region allocated by the OS to the program.

---

## Code Written

### Code 1 — Division by Zero
```c
#include <stdio.h>

int divide(int a, int b) {
    return a / b;
}

int main() {
    int x = divide(10, 0);
    printf("%d\n", x);
    return 0;
}
```

**gdb output:**
```
Program received signal SIGFPE, Arithmetic exception.
0x000055555555515b in divide (a=10, b=0) at buggy.c:4
4    return a/b;
```

`SIGFPE` = Signal Floating Point Exception — raised on fatal arithmetic errors including integer division by zero. gdb identified the exact function, arguments, file, and line.

---

### Code 2 — Infinite Recursion (Stack Overflow)
```c
#include <stdio.h>

int factorial(int n) {
    return n * factorial(n);  // bug: n never changes, no base case
}

int main() {
    int n = 5;
    int result = factorial(n);
    printf("%d\n", result);
    return 0;
}
```

**gdb output:**
```
Program received signal SIGSEGV, Segmentation fault.
0x0000555555555155 in factorial (n=<error reading variable: 
Cannot access memory at address 0x7fffff7feffc>) at buggy2.c:4
```

The backtrace showed hundreds of identical frames — `factorial (n=5) at buggy2.c:10` — repeating until the stack was exhausted. Frame #0 showed `<error reading variable>` because the stack pointer had already walked past the memory allocated to the program.

**Root cause:** No base case, `n` never changes, each call pushes a new stack frame that is never freed. Stack overflows → `SIGSEGV`.

---

## Conceptual Exit Question

**What is a stack frame? When `factorial(3)` calls `factorial(3)` infinitely — what does the backtrace show, and why does it eventually crash?**

A stack frame is the memory block allocated on the stack for a single function call. It holds the function's arguments, local variables, and the return address — the address the CPU jumps back to when the function returns.

When `factorial(3)` calls `factorial(3)` with no base case, each call pushes a new stack frame onto the stack. None of these frames are ever freed because the function never returns. The backtrace shows the same frame — `factorial (n=3)` — repeated hundreds of times. The stack is a fixed-size region; once it is exhausted, the next push attempts to write past its boundary, triggering a segmentation fault (`SIGSEGV`) and crashing the program.