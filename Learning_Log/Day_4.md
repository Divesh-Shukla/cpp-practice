## Day 4 — 17 March, 2026  
### Topic: Compilation Pipeline — Source → Object → Executable

---

## 1. Core Pipeline (No vagueness)

Write the full pipeline:

.c → .i → .s → .o → executable

main.c
  |(preprocessor)
main.i -> expanded source code file(resolved headers and macro defintion)
  |(compiler)
main.s -> assembly code(CPU-specific instruction)
  |(assembler)
main.o -> object file(machine code + metadata + symbol table + relocation info)
  |(linker)
app -> executable program


## 2. Preprocessing (Mechanism, not definition)

- What happens to `#include`?
- The #include preprocessor directive is replaces the content of the mentioned file with all the contents of the named file, it literally copy pastes the content of include file into the source file
- What happens to macros?
- During preprocessing of the source code file, the preprocessor substitutes the text where the macros are present in source code.(wrong(initial understanding):replaces all the Macros in the source code with the specified value of the macro).
- What does the compiler ACTUALLY see?
- The compiler never sees the preprocessor directive, what compiler recieves is an file with .i extension which is the expanded source code file with all the headers included and the macros resolved. The compiler operates on this translation unit.

Then run:
gcc -E main.c
- The above command shows the preprocessed code or expanded code.

Paste 5–10 relevant lines and explain:
- where your header content appears
### Include guards behaviour
- First inclusion if not defined or included, the code inside the ifndef get inserted.
- Macro got defined(written as it is given by ai, only this line)
- Second inclusion -> if already included, second inclusion is avoided due to #ifndef check.

This prevent multiple declarartion in the same transtaltion unit.

---

## 3. Translation Unit (CRITICAL)

Answer:
- What is a translation unit?
- A translation unit is the expanded file that is recieved by the compiler for the compilation. It is the file after the preprocessing with included headers and substituted macros. It is the unit of compilation.
- What does one `.c` file become after preprocessing?
- The `.c` file after preprocessing becomes translation unit which has an extension `.i`.

Write:
> “The compiler sees the code with header include and macros resolved. The compiler sees the entire translation unit (single source file + included headers), but it does NOT see other `.c` files. Cross-file connections are handled later by the linker. The prototypes of function and macros are already replaced and in place.”

---

## 4. Object File Anatomy

### Machine Code
- The actual low-level instructions generated from the source code.
- Not complete, because function calls may still reference symbols instead of actual addresses.

### Symbol Table
- A table storing all symbols (functions/variables) used in the file.
- Contains:
  - Defined symbols (T, D, B)
  - Undefined symbols (U)
- Used by linker to resolve references.

### Relocation Info
- Information about where symbols are used in the code.
- Tells the linker:
- “At this location, replace symbol X with actual address”

## 5. Symbols (Core Section — don’t mess this up)

Define:
> What is a symbol?
- A symbol basically is a name that represents a memory location or function and it is tracked by the compiler and linker(for linking calls and definition).
-If undefined (U), the address is not yet known and will be resolved during linking.

Whenever we write a function or variable, all this lives inside a memory location, so internally all this becomes:-
  name -> some memory address where it resides.
and this mapping which connects the name and address
  name -> address
is what we basically call a symbol.

The main role of symbol is that it holds the address of the different objects until linking happens.
Because the CPU onlu understands:
call 0x498749(address)
store at 0x8734874(address).....etc

All these symbols live inside a symbol table in the object code file.

#### Process:
1. After compilation 
- the object file that is created has symnbols but not all symbols has address of the function or in simple term the the name' symbol is not in this file.
2. After linker
- The linker finds the symbol for the unaddressed name then assigns the actual address to the undefined symbol.Now the symbol is mapped to an address, that is the address of the function or given varaible.



### Types you observed:
- T → stands for Text/Code. This symbol tells us that name has a specific address that means it is defined. And it is stored int the text(code) section.
- U → stands for Undefined. This means that the given symbol's name is not mapped to any address. Therefore it is undefined, meaning it needs add but it's not present here in the object file.
- D → Initialized global variable (stored in data section)
- B → Uninitialized global variable (stored in BSS section, zero-initialized at runtime)
There are other 2 symbols too, D and B.

Run:
nm main.o  
nm mathutils.o  

Paste output and explain EACH line:
- what symbol
- defined or undefined
- why

---

## 6. Linking (Mechanism)

Explain:

- What problem linker solves
The linker solves the problem of the independent compilation that mutilple files can't be compiled at once, so the linker can link function from differnt file to the calls present in different files.
- How it uses symbols
- Symbols basically are name and address mapping so what linker does is replace the name in code to the address of the given function or variable.
- The linker resolves symbol references by replacing symbolic references with actual memory addresses.
- “Linker matches U (undefined symbols) from one file with T/D/B (defined symbols) from another”

Write this explicitly:
> “Linker matches U (undefined symbols) from one file with T/D/B (defined symbols) from another”

### Process:
1. Linker opens all object files.
2. Then what the linker does is make a giant table of all the symbols from all the files.
3. Then it tries to find the text/code(T) for all the matching  undefined symbols(U) from all the different object files
4. replace the U reference(what is u refernce stiil not clear) with the actual address of the T symbol.
5. Writes the final executable with all the real adresses.

## 7. Failure Case 1 — Missing Definition

What you did:
- removed function definition

What happened:
- the linker gave an error "undefined reference to `function`"

Explain using symbols:
- which symbol was `U`
- why no matching `T`
- This happens because the object file has function call(U function) but no matching defintion(T fucntion) of the function that the code is trying to call therefore it throws an error.

---

## 8. Failure Case 2 — Multiple Definition

What you did:
- defined same function twice

Error:
- the linked gives an error"redefinition of `function`"

Explain:
- how many `T` symbols existed
- This error happens because for a given function call two T function exists, that is two symbols exists with two addresses. That is linker detects multiple definition of the same symbol(multiple T entries) and fails because each symbol must have ony one definition.
- why linker failed
- Linker fails to recognize with address to link the call to.

---

## 9. Header Files (Real Purpose)

### Declaration vs Definition

- Declaration:
  int add(int, int);
  → tells compiler the function exists (no symbol created)

- Definition:
  int add(...) { ... }
  → creates symbol (T)

### Why headers are needed
- Allow compiler to check function signatures across files
- Enable independent compilation of translation units

### Why multiple inclusion does not break
- Include guards prevent duplicate declarations in same translation unit
- Declarations do not create symbols, so no linker conflict

## 10. Mental Model (This is your real output)
- Each `.c` file is compiled independently into an object file containing machine code and symbols.  
- These object files may contain unresolved symbols (U).  
- The linker combines all object files and resolves these symbols by matching them with definitions (T/D/B).  
- The final executable is produced after all symbol references are resolved.

## 11. Commands You Used (Minimal, not a list dump)

- gcc -c → compiles source into object file
- gcc main.o mathutils.o -o app → links object files into executable
- nm → shows symbol table of object file
- gcc -E → shows preprocessed code (translation unit)

## 12. Today’s Most Important Insight

- How multiple definition leads to error, the actual mechanism, how two addresses exist for the same name and it fails because linker needs only one symbol for a name, only one definition.
- How multiple declarartions do not cause error because they declarations do not create a symbol.
## 13. One Confusion (Mandatory)

- I still don't completely understand symbols properly.
-  I also do not understand the working of linker using symbol properly.
