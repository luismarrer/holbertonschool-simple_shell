#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *path = getenv("PATH");
	char *token;
	char *delim = ":";

	if (path == NULL)
	{
		printf("The PATH environment variable is not set.\n");
		return (1);
	}

	printf("Directories in PATH:\n");
	token = strtok(path, delim);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, delim);
	}
	return (0);
}
