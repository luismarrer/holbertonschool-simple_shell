#include "simple_shell.h"

/**
 * print_environment - Prints all environment variables.
 *
 * @env: Array of strings with environment variables.
 */

void print_environment(char **env)
{
	int i = 0;

	if (env == NULL)
	{
		printf("Error: No environment variables found.\n");
		return;
	}
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

