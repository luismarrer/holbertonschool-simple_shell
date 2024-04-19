#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

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
 * main -
 *
 * Return: returns 0 always.
 */

extern char **environ;

int main(void)
{
	ssize_t read;
	char *buffer = NULL;
	size_t len = 0;
	const char *delim = " \n\t";
	char **tokens;
	int status, i;
	pid_t child_pid;


	while (true)
	{
		printf("#cisfun$ ");
		read = getline(&buffer, &len, stdin);
		if (read == -1)
		{
			free(buffer);
			return (1);
		}
		tokens = split_strings(buffer, delim);
		if (tokens == NULL)
		{
			free(buffer);
			continue;
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			free(buffer);
			return (1);
		}
		else if (child_pid == 0)
		{
			if (execve(tokens[0], tokens, environ) == -1)
				perror("Error:");
		}
		else
			wait(&status);

		for (i = 0; tokens[i] != NULL; i++)
			free(tokens[i]);
		free(tokens);
		free(buffer);
		buffer = NULL;
	}
	return (0);
}
