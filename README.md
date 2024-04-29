# C - Simple Shell Final Project

This project is a collaboration among three students at Holberton Coding School. Our main goal is to develop a simple UNIX command interpreter that emulates basic shell behavior.

## Authors

- [Nissel Sanchez](https://github.com/niniisg)
- [Luis Marrero](https://github.com/Luismarrer)
- [Emmanuel Torres](https://github.com/Emahnny)


## Project Description

This project involves creating a simple shell, a basic command line interpreter similar to UNIX shells. It is designed to interpret and execute commands in an interactive mode and non-interactive mode.

## Learning Objectives

At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

### General

- Who designed and implemented the original Unix operating system
- Who wrote the first version of the UNIX shell
- Who invented the B programming language (the direct predecessor to the C programming language)
- Who is Ken Thompson
- How does a shell work
- What is a pid and a ppid
- How to manipulate the environment of the current process
- What is the difference between a function and a system call
- How to create processes
- What are the three prototypes of main
- How does the shell use the PATH to find the programs
- How to execute another program with the execve system call
- How to suspend the execution of a process until one of its children terminates
- What is EOF / "end-of-file"?

## Requirements

### General

- Allowed editors: `vi`, `vim`, `emacs`
- All your files will be compiled on Ubuntu 20.04 LTS using `gcc`, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)

### List of allowed functions and system calls+
- all functions from string.h
- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `getpid` (man 2 getpid)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `printf` (man 3 printf)
- `fprintf` (man 3 fprintf)
- `vfprintf` (man 3 vfprintf)
- `sprintf` (man 3 sprintf)
- `putchar` (man 3 putchar)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (__xstat) (man 2 stat)
- `lstat` (__lxstat) (man 2 lstat)
- `fstat` (__fxstat) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)

### Compilation

- `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

## Documentation

### Files

- `env.c`: Prints environment variables.
- `execute_command.c`: Handles input command processing, verifies `PATH`, checks file accessibility, manages child processes, and utilizes `execve` for execution.
- `my_own_func.c`: Custom implementations of standard library functions.
- `simple_shell.c`: Includes the main function, string parsing, memory management, and built-in commands handling (`env`, `exit`).

### Usage

![This is an image with a interaction example of our simple shell.](ShellExample.png)


## Tasks

### 0. README, man, AUTHORS

**Mandatory**

- Write a README
- Write a man page for the shell.
- Include an AUTHORS file at the root of the repository, listing all contributors.

### 1. Betty would be proud

**Mandatory**

Write code that passes the Betty checks for beautiful code.

### 2. Simple shell 0.1

**Mandatory**

Write a UNIX command line interpreter.

### 3. Simple shell 0.2

**Mandatory**

Simple shell 0.1 +:

- Handle command lines with arguments

### 4. Simple shell 0.3

**Mandatory**

Simple shell 0.2 +:

- Handle the PATH
- Do not call fork if the command doesn’t exist

### 5. Simple shell 0.4

**Mandatory**

Simple shell 0.3 +:

- Implement the `exit` built-in, which exits the shell
- Usage: `exit`
- No need to handle any argument to the built-in exit

### 6. Simple shell 1.0

**Mandatory**

Simple shell 0.4 +:

- Implement the `env` built-in, which prints the current environment
