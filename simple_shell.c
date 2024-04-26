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
	const char *delims = " \n\t";
	char **tokens;
	int last_command_status = 0;
	bool is_interactive = isatty(STDIN_FILENO);

	while (true)
	{
		if (is_interactive)
			printf("#cisfun$ ");

		read = getline(&buffer, &len, stdin);
		if (read == -1)
		{
			printf(is_interactive ? "\n" : "");
			free(buffer);
			break;
		}
		tokens = split_strings(buffer, delims);
		if (tokens && tokens[0])
		{
			if (handle_command(tokens, env, buffer, &last_command_status))
				continue;
			last_command_status = execute_command(tokens, env);
		}
		else
		{
			last_command_status = 0;
		}
		free_memory(tokens, buffer);
		buffer = NULL;
	}
	return (last_command_status);
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
			words = _realloc(words, capacity * sizeof(char *),
					2 * capacity * sizeof(char *));
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
	words = _realloc(words, n_words * sizeof(char *),
			(n_words + 1) * sizeof(char *));
	words[n_words] = NULL;
	free(input_copy);
	return (words);
}

/**
 * free_memory - This function clears memory
 * before exiting the simple shell when using "exit".
 *
 * @tokens: A pointer to an array of strings.
 *
 * @buffer: A pointer to the input string buffer.
 */

void free_memory(char **tokens, char *buffer)
{
	int i;

	if (tokens)
	{
		for (i = 0; tokens[i] != NULL; i++)
		{
			free(tokens[i]);
		}
		free(tokens);
	}
	free(buffer);
	buffer = NULL;
}

/**
 * handle_command - Handles execution of built-in commands.
 *
 * @tokens: Tokens parsed from input.
 *
 * @env: Environment variables.
 *
 * @buffer: Buffer holding the input string.
 *
 * @status: Pointer to the status of the last executed command.
 *
 * Returns: 0 otherwise.
 */

int handle_command(char **tokens, char **env, char *buffer, int *status)
{
	if (strcmp(tokens[0], "env") == 0)
	{
		print_environment(env);
		*status = 0;
		free_memory(tokens, buffer);
		return (1);
	}
	else if (strcmp(tokens[0], "exit") == 0)
	{
		free_memory(tokens, buffer);
		exit(*status);
	}
	return (0);
}

