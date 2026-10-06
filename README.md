# C/C++ Debugging Challenges

**A collection of intentionally buggy C programs designed to teach real-world debugging skills.**

This repository contains two complete debugging assignments that help students master the most common compile-time and run-time errors encountered when writing C/C++ programs. Both challenges produce a visually satisfying result once all bugs are fixed, making the learning process engaging and rewarding.

## Learning Objectives

By completing these assignments students will:

- Read and interpret compiler error messages
- Distinguish between compile-time, run-time, and logic errors
- Practice systematic debugging techniques (print statements, debuggers, binary search)
- Recognize and fix the most common C/C++ pitfalls
- Produce clean, working programs that create enjoyable visual output

## The 10 High-Frequency Bugs

Both assignments deliberately contain the following classic bugs:

1. **Missing / wrong headers** → undeclared identifiers (`malloc`, `strcpy`, etc.)
2. **Syntax errors** that cascade (missing `;`, mismatched braces)
3. **`=` instead of `==`** in a condition
4. **Uninitialized variable** used in a calculation or loop
5. **Off-by-one / array-bounds** error (`i <= n` on a size-`n` array)
6. **Buffer overflow** (writing past the end of a fixed-size buffer)
7. **Null-pointer / bad allocation handling** (possible segmentation fault)
8. **Infinite loop** caused by a wrong termination condition
9. **Integer-division / type** subtlety that produces incorrect results
10. **Memory mismanagement** (incorrect `free`, missing `free`, or freeing the wrong pointer)

## Assignment 1: Rocket Launch Simulator

**Theme:** A professional ASCII-art rocket launch with countdown, rising animation, starfield, launch pad, and animated exhaust flames.

**Goal when fixed:**  
A smooth, full-screen animation of a rocket lifting off, complete with status readouts and a polished “Mission Success” ending screen. The console window stays open until the user presses Enter.

**Files**
- `rocket_launch_buggy.c` – the version students receive
- `rocket_launch_fixed.c` – the complete, error-free reference solution

**Key features of the fixed program**
- ANSI clear-screen animation
- Detailed multi-line rocket
- Flickering exhaust
- Twinkling starfield
- Launch pad
- Portable delay function
- Clean final pause

## Assignment 2: Matrix Digital Rain

**Theme:** Classic “Matrix-style” falling digital rain (green characters cascading down the terminal).

**Goal when fixed:**  
A clean, atmospheric digital-rain animation that runs for a set number of frames and then displays a success message (“SYSTEM SECURE”). The program ends with a “Press Enter to exit” prompt.

**Files**
- `matrix_rain_buggy.c` – the version students receive
- `matrix_rain_fixed.c` – the complete, error-free reference solution

**Key features of the fixed program**
- Multiple independent falling columns
- Brighter “head” characters and dimmer trails
- Deterministic but varied character generation
- Smooth frame timing
- Proper memory management
- Clean final screen

## How to Use This Repository

```bash
# Clone the repository
git clone <repository-url>
cd <repository-name>

# Compile a fixed version (example)
gcc -Wall -Wextra -std=c11 -o rocket rocket_launch_fixed.c
./rocket

gcc -Wall -Wextra -std=c11 -o matrix matrix_rain_fixed.c
./matrix
```

Both programs use only standard C11 and ANSI escape sequences. They work on modern Windows Terminal, macOS, and Linux terminals.

---

## Instructions for Students

1. Choose one assignment (or complete both).
2. Copy the corresponding `*_buggy.c` file.
3. Attempt to compile it. Read the compiler errors carefully.
4. Fix the bugs one at a time. Re-compile after each change.
5. When the program runs, observe any remaining run-time or logic problems (crashes, infinite loops, incorrect visuals, memory issues).
6. Use print statements or a debugger (`gdb`, IDE debugger, etc.) as needed.
7. Continue until the program matches the behavior described in the assignment goal.
8. Compare your final result with the provided `*_fixed.c` only after you believe you have solved it (or as directed by your instructor).

**Recommended compiler flags**
```bash
gcc -Wall -Wextra -std=c11 -o program program.c
```

**Optional memory checking** (Linux/macOS)
```bash
valgrind ./program
```

## Instructions for Instructors

- Distribute only the `*_buggy.c` files to students.
- Keep the `*_fixed.c` files as private reference solutions for grading.
- Both assignments are self-contained and require no external libraries.
- Suggested lab time: 60–90 minutes per assignment for intermediate students.
- You may increase difficulty by asking students to add features after fixing the bugs (color variations, adjustable speed, user input, etc.).
- The final “Press Enter to exit” ensures the console window remains visible on all platforms, including Windows.

### Ways to Contribute
- Improve documentation or add more detailed explanations
- Add additional test cases or edge-case discussions
- Create new debugging challenges following the same 10-bug guideline
- Improve portability or add optional enhanced versions (e.g., color themes)
- Fix typos or clarify instructions
- Add solutions in other languages (C++, Rust, etc.) as separate folders

### Contribution Process
1. Fork the repository
2. Create a new branch (`git checkout -b feature/your-feature`)
3. Make your changes
4. Commit with clear messages
5. Push to your fork
6. Open a Pull Request and describe what you changed

Please keep new challenges consistent with the existing style:
- Compelling visual result when fixed
- Exactly the same 10 high-frequency bug categories
- Both a buggy and a fully corrected version
- Clear README section for the new challenge

## License

This project is released under the MIT License. See the `LICENSE` file for details.


