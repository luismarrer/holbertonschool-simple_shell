
/**
 * print_environment - Prints all environment variables.
 *
 * @env: Array of strings with environment variables.
 *
 */

{
	int i = 0;

void print_environment(char **env);

    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
}
