#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int ac, char **av)
{
	struct stat st;
	int i;
	
	if (ac < 2)
	{
		printf("Usage: %s filename ...\n", av[0]);
		return (1);
	}

	for (i = 1; i < ac; i++)
	{
		if (stat(av[i], &st) == 0)
		{
			printf("%s found in current directory\n", av[i]);
		}
		else
		{
			printf("%s not found in current directory\n", av[i]);
		}
	}
	return (0);
}
