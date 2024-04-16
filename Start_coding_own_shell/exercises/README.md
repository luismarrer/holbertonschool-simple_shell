# Exercises Directory

This directory contains individual exercises that I have developed to practice
the concepts taught in the "Concept: Everything you need to know to start coding your own shell."
These exercises help reinforce the theoretical knowledge through practical implementation.

## Working with These Exercises

Each file in this directory is a standalone exercise.
Most of these exercises are from "Everything you need to know to start coding your own shell".

## List of Exercises

- `ppid.c`: This exercise demonstrates how to retrieve and print the parent process ID (PPID) using the `getppid()` function.
- `pid_max`: This script prints the maximum value that a process ID (PID) can be on this Linux system.
It reads the value from `/proc/sys/kernel/pid_max` and displays it, providing insight into system limits for PID values.
- `av.c`: This exercise demonstrates how to print all the command-line arguments passed to the program without using the argument count (`ac`).
The program iterates over the argument vector (`av`), which is an array of strings representing the command-line arguments,
and prints each argument until it reaches the `NULL` terminator that marks the end of the array.
This example is particularly useful for understanding how to process command-line arguments in programs where the number of
arguments is not predetermined.

