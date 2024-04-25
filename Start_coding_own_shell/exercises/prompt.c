#include <stdio.h>
#include <stdlib.h>
#define TRUE 1

/**
 * main - Prints "$ ", wait for the user to enter a command,
 * prints it on the next line.
 *
 * Return: 0 always
 */

int main(void)
{
	ssize_t read;
	char *buffer = NULL;
	size_t len = 0;

	while (TRUE)
	{
		printf("$ ");
		read = getline(&buffer, &len, stdin);
		if (read == -1)
		{
			free(buffer);
			return (0);
		}

		printf("%s", buffer);
	}

	return (0);
}
