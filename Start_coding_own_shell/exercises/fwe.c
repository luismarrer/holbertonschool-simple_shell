#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - program that executes the command 'ls -l /tmp' in 5 different child processes.
 * Each child should be created by the same process (the father).
 * Wait for a child to exit before creating a new child.
 *
 * Return: always return 0.
 */

extern char **environ;

int main(void)
{
	pid_t pid;
	int i;
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};
	int status;

	for (i = 0; i < 5; i++)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
				perror("Error:");
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}
