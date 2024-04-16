# Examples Directory

This directory contains code examples that demonstrate specific concepts required for building a shell.
These examples are provided as part of the learning resources from the
"Concept: Everything you need to know to start coding your own shell."

## Using These Examples

You can compile and run each example to see how it works.
These examples are intended to provide a hands-on way to understand the coding
techniques and system calls involved in creating a shell.

## List of Examples

- `env-main.c`: This program prints out the environment variables available to it.
  It demonstrates how to access and iterate through the `env` parameter provided to the `main()` function in a C program.
- `exec.c`: Demonstrates the use of the `execve()` system call, which replaces the current process with a new program.
  This example specifically runs the `ls` command to list the contents of the `/usr/` directory and shows how control
  does not return to the original program after `execve()` if it is successful.
- `fork.c`: This example shows how to use the `fork()` system call to create a new process.
  It outputs the process ID of both the parent and the newly created child process, illustrating how `fork()`
  returns different values in the parent and child processes.
- `fork1.c`: An extension of the `fork.c` example, this program further explores process creation.
  It differentiates the output based on whether the code is running in the parent or the child process,
  demonstrating how to check if a process is a child or a parent and handle process logic accordingly.
- `pid.c`: Demonstrates how to retrieve and print the process ID (PID) of the current process using `getpid()`,
  which is useful for identifying processes within a system.
- `stat.c`: This example uses the `stat()` function to retrieve information about a file specified by the user.
  It checks whether the file exists and prints the result, showing how to use command-line arguments and handle file status checks.
- `wait.c`: Illustrates how to use `fork()` and `wait()`.
  This program creates a child process that delays for a few seconds while the parent process waits for the child's
  completion before continuing, demonstrating process synchronization.
