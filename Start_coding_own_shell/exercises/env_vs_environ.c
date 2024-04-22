#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(int ac __attribute__((unused)), char **av __attribute__((unused)), char **env)
{
	printf("Address of 'env' parameter: %p\n", (void *)env);
	printf("Address of 'environ' global variable: %p\n", (void *)environ);

	if (env == environ)
	{
		printf("Both 'env' and 'environ' point to the same location.\n");
	}
	else
	{
		printf("The addresses are different.\n");
	}

	return (0);
}
