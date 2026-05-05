# Mini Shell Interpreter (C++)

## Description
A simple Unix-like mini shell implemented in C++ using Operating System concepts like process creation and execution.

## Features
- Execute system commands (ls, pwd, echo, etc.)
- Command parsing using stringstream
- Process creation using fork()
- Command execution using execvp()
- Parent-child synchronization using wait()

## Technologies Used
- C++
- Linux System Calls (fork, execvp, wait)

## How to Run

```bash
g++ mini_shell.cpp -o shell
./shell
