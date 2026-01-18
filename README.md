# Mini Shell (C)

## Overview
This project is a minimal Unix-style shell implemented in C. It processes
commands from a batch input file and executes a limited set of custom
programmer-defined commands, writing all output to a specified output file.

The shell is designed to demonstrate systems programming concepts such as
process control, file handling, and command parsing.

---
## Supported Commands
- `showme <filename>` — Display the contents of a file
- `junk <filename>` — Delete a file
- `createf <filename>` — Create an empty file
- `lstdir` — List directory contents
- `parse_log <input> <output>` — Execute the log parser program

---

## Files
- `shell.c` — Shell implementation and command execution logic
- `README.md` — Project documentation

---

## Compilation
Compile the shell using GCC:

#Bash
gcc shell.c -o mini_shell

Usage

Run the shell with an input command file and an output file:

./mini_shell commands.txt output.txt
