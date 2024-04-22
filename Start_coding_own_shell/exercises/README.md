# Exercises Directory

This directory contains individual exercises that I have developed to practice
the concepts taught in the "Concept: Everything you need to know to start coding your own shell."
These exercises help reinforce the theoretical knowledge through practical implementation.

## Working with These Exercises

Each file in this directory is a standalone exercise.
Most of these exercises are from "Everything you need to know to start coding your own shell".

## List of Exercises

### PID & PPID
- `ppid.c`: This exercise demonstrates how to retrieve and print the parent process ID (PPID) using the `getppid()` function.
- `pid_max`: This script prints the maximum value that a process ID (PID) can be on this Linux system.
It reads the value from `/proc/sys/kernel/pid_max` and displays it, providing insight into system limits for PID values.

### Arguments
- `av.c`: This exercise demonstrates how to print all the command-line arguments passed to the program without using the argument count (`ac`).
The program iterates over the argument vector (`av`), which is an array of strings representing the command-line arguments,
and prints each argument until it reaches the `NULL` terminator that marks the end of the array.
This example is particularly useful for understanding how to process command-line arguments in programs where the number of
arguments is not predetermined.
- `prompt.c`: This program continuously prompts the user with a "$ " symbol,
waits for the user to enter a command, and then prints that command on the next line.
It utilizes `getline()` to read an entire line from stdin, handling dynamic input sizes automatically.
The loop continues indefinitely until an End-of-File (EOF) condition is encountered
(typically triggered by Ctrl+D on the keyboard), at which point the program cleans up and exits.
This exercise is crucial for understanding user input handling and dynamic memory management in C programming.
- `strtok.c`: This program provides a practical demonstration of using the `strtok` function to tokenize a string read from the user input.
It continuously reads lines from the standard input, breaks each line into tokens based on spaces, and prints each token on a new line.
This example is essential for understanding the basics of string tokenization in C.
- `strtok2.c`: This program demonstrates a more advanced usage of tokenizing strings using a custom function that splits a string
into an array of words based on specified delimiters.
It showcases dynamic memory management and the use of `strtok` within a user-defined function context.

### Exercise: fork + wait + execve
- `fwe.c`: This exercise demonstrates advanced process management where the `ls -l /tmp`
command is executed in five separate child processes, each created sequentially by a single parent process.
The parent process ensures it waits for the completion of one child before initiating the next, effectively
managing child processes without overlapping executions.
This example not only illustrates the use of `fork()` to spawn new processes but also integrates `execve()`
to execute a system command within each child.
Additionally, it uses `wait()` to synchronize the termination of child processes with the creation of new ones,
thus avoiding the creation of zombie processes and ensuring that system resources are managed efficiently.
This program provides practical insights into process creation, execution, and synchronization
within the context of Unix-like systems programming.

### Exercise: super simple shell
- `shell.c`: This program is a simple implementation of a Unix-like shell
that can execute commands using their full paths without any arguments.
The shell runs in a continuous loop, displaying a prompt `#cisfun$`
to the user and waiting for command input.
Upon receiving a command, the shell splits the command string into tokens
to separate the command from its potential arguments,
though this version only executes the command without any arguments.
The shell utilizes `fork()` to create a child process for command execution and `execve()`
to run the command in the child process, using the system's environment variables.
After executing the command, the shell waits for the process to finish using `wait()`,
ensuring all resources are properly managed and no zombie processes are left.
This implementation is particularly useful for understanding the basics of process creation,
command execution, and simple state management in a shell environment.

### File information

- `_which.c`: This exercise demonstrates how to check for the existence of
specified files within the current directory using the `stat` system call.
The program takes one or more filenames as command-line arguments and checks
each one to determine if it exists in the directory from which the program is run.
For each file, it prints a message indicating whether the file was found or not.
