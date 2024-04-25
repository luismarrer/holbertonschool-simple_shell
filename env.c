#include "simple_shell.h"

/**
 * print_environment - Prints all environment variables.
 *
 * @env: Array of strings with environment variables.
 */

void print_environment(char *env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		printf("%s\n", env[i]);
	}
}
