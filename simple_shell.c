#include "simple_shell.h"

/**
 * main - This program is a simple shell.
 *
 * @ac: Argument counter (not used).
 *
 * @av: Array of string with arguments (not used).
 *
 * @env: Array of strings with environment variables.
 *
 * Return: 0 succes
 */

int main(int ac __attribute__((unused)),
		char **av __attribute__((unused)),
		char **env)
{
	ssize_t read;
	char *buffer = NULL;
	size_t len = 0;
	const char *delim = " \n\t";
	char **tokens;
	int i;
	bool is_interactive = isatty(STDIN_FILENO);

	while (true)
	{
		if (is_interactive)
		{
			printf("#cisfun$ ");
		}
		read = getline(&buffer, &len, stdin);
		if (read == -1)
		{
			free(buffer);
			if (is_interactive)
			{
				printf("\n");
			}
			break;
		}
		tokens = split_strings(buffer, delim);
		if (tokens)
		{
			execute_command(tokens, env);
			for (i = 0; tokens[i] != NULL; i++)
			{
				free(tokens[i]);
			}
			free(tokens);
		}
		free(buffer);
		buffer = NULL;
	}
	return (0);
}

/**
 * split_strings - Splits a string into words based on specified delimiters.
 *
 * @input: The string to split.
 *
 * @delims: A string containing the delimiter characters.
 *
 * Return: A dynamically allocated array of words,
 * terminated with a NULL pointer.
 */

char **split_strings(const char *input, const char *delims)
{
	int capacity = 10;
	char **words = malloc(capacity * sizeof(char *));
	int n_words = 0;
	char *token;
	char *input_copy;

	if (!words)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return (NULL);
	}
	input_copy = strdup(input);
	if (!input_copy)
	{
		free(words);
		return (NULL);
	}
	token = strtok(input_copy, delims);
	while (token != NULL)
	{
		if (n_words >= capacity)
	{
			capacity *= 2;
			words = realloc(words, capacity * sizeof(char *));
			if (!words)
			{
				free(input_copy);
				fprintf(stderr, "Memory allocation failed\n");
				return (NULL);
			}
		}
		words[n_words++] = strdup(token);
		token = strtok(NULL, delims);
	}
	words = realloc(words, (n_words + 1) * sizeof(char *));
	words[n_words] = NULL;
	free(input_copy);
	return (words);
}

/**
 * execute_command - It is an auxiliary function that
 * calls the commands to be executed.
 *
 * @tokens: Command to execute.
 *
 * @env: The environment variables.
 */

void execute_command(char **tokens, char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
	}
	else if (pid == 0)
	{
		if (execve(tokens[0], tokens, env) == -1)
		{
			perror("Error");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);
}
