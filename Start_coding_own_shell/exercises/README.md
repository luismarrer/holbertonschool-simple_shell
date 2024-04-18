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


