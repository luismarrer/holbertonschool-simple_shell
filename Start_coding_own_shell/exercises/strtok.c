#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * main - Function to try to understand strtok.
 *
 * Return: returns 0 always.
 */

int main(void)
{
	ssize_t read;
	char *buffer = NULL;
	size_t len = 0;
	const char *delim = " ";
	char *token;

	while(true)
	{
		printf("$ ");
		read = getline(&buffer, &len, stdin);
		if (read == -1)
		{
			free(buffer);
			return (0);
		}
		else if (buffer != NULL)
		{
			token = strtok(buffer, delim);
			while (token != NULL)
			{
				printf("%s\n", token);
				token = strtok(NULL, delim);
			}
		}
	}

	free(buffer);
	return (0);
}
