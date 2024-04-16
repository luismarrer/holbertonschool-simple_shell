#include <stdio.h>
#include <stdlib.h>

/**
 * main - Program that prints all the arguments.
 *
 * Return: Always return 0.
 */

int main(int ac __attribute__((unused)), char **av)
{
	char **current_arg = av;

	while (*current_arg != NULL)
	{
		printf("%s\n", *current_arg);
		current_arg++;
	}

	return (0);
}
