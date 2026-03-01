# Day 1
	 
## Session 1
**What I Did:**
- Created directories and navigated directories using terminal commands.
- Created a hello.cpp C++ source code file using the touch command and coded it using the nano command.
- Compiled the file with command: g++ hello.cpp -o hello
- Ran the executable code with: ./hello

**What I learned:**
- Terminal commands: pwd,cd, cd.., mkdir, touch, nano.
- g++ is the compiler.
- g++ hello.cpp command creates the executable code file of hello.cpp source code with a name a.out.
- -o specifies the output file name.
- ./ runs the executable code.


## Session 2
**What I Did:**
- Wrote a source code file with deliberate errors.
- Used -Wall and -Wextra in the command to create the executable command.
- On running the command"g++ -Wall -Wextra flags_demo.cpp -o flags_demo" the compiler generated warnings.

**Flags learned:**
- -Wall: enabled all warning
- -Wextra: enabled extra warnings
- std=c++17: Use C++17 standard

**Why it matters:**
- Warnings catches before it turns into a runtime error.

**My standard compile command:** 
- g++ -std=c++17 -Wall -Wextra file.cpp -o file

## Session 3: Problem Solving - COMPLETE

**What I did:**
Solved 5 problems using pure terminal workflow:
1. Sum of N numbers - sum_of_n.cpp
2. Find maximum - maxNum_arr.cpp
3. Reverse array - reverse-arr.cpp
4. Prime checker - isPrime.cpp
5. Fibonacci - fibonacci.cpp

**Bonus:** With help from ChatGPT, wrote improved version of find maximum that handles edge cases (maxNum_arr_robust.cpp)

**Compilation command now muscle memory:**
g++ -std=c++17 -Wall -Wextra file.cpp -o file

**What became automatic:**
- Navigate with cd
- Create file using touch
- Edit file using nano
- Compile with flags
- Run code with ./file
- Git add/commit after each problem

**Time taken:** [2 Hours]

**Core learning (Session 3):**
- Writing and executing C++ code entirely in terminal
- Terminal workflow is now natural, not forced
- Confidence building with compile-run-test cycle

**Bonus learning (exception handling):**
- Explored try-catch blocks for error handling
- try block: code that might throw an error
- catch block: code that catches and handles the thrown error
- Learned about std::bad_alloc exception for memory allocation failures
- Understood difference between throwing exceptions vs returning values

**Confidence level:** [6/10] on terminal workflow
