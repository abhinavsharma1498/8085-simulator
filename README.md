# 8085-simulator
This project gives you a simulator for the 8085 microprocessor.

# Motivation
8085 is a part of the UGC curriculum and we as students require a kit to practice 8085 based assembly programs on. So in order to provide a cheap solution to this problem, we started this project.

# Build status
Successful build

# Code style
Standard C++14 style

# Compiler used
g++ 5.4.0

# Features
The projects features an easy to use debugger which can be invoked using --debugger option.
It also gives user the freedom to either type the assembly program at run time or just give path to an assembly program on disk.

# Libraries used
STL libraries are intensively used.

# Installation
Setting up the machine (Linux):
1. Open terminal.
2. Install g++ using "sudo apt install g++" (without quotes).
Building the project:
1. Open terminal and goto the project directory using cd command.
2. Create a build folder using "mkdir build" (without quotes).
3. Build the project using "make" (without quotes).

# How to use
Running the program:
1. Open terminal and goto the project directory using cd command.
2. Now run the program using either of the following instructions:
   ./8085 (To run the program while typing the program)  
   ./8085 /home/...path to assembly program (To run the program using program on the disk)  
   ./8085 --debugger (To ru program while typing it in debugger mode)  
   ./8085 /home/...path to assembly program --debugger (To run a program on difk in debugger mode)  

# Example code available
1. greater.asm -> Take two values from user (at 2050 and 2051) and store the larger value at 3050.
2. smaller.asm -> Take two values from user (at 2050 and 2051) and store the smaller value at 3050.
3. negative.asm -> Take value from user (at 2050) and store its negative at 3050.
4. sum.asm -> Take four values from user (2050, 2051, 2052, 2053) and store their sum at 3050.
5. sum16.asm -> Take two 16 bit values from user (2051, 2050) and store their sum at (3051, 3050).

# Contribute
Ways to contribute to this project:
1. Add sub routine instructions.
2. Solve problem with debugger (It runs properly but exits with segmentation fault).

# Credits
Akshay Rajput sir -> For inspiring us with the idea.  
Hemant Pokheriya sir -> For teaching us the 8085 instruction set.  

# Project contributers
Abhinav Sharma  
Rohan Deoli
