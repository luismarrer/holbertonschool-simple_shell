#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(void)
{
	ssize_t read;
	char *buffer = NULL;
	size_t len = 0;
	const char *delim = " ";
	char **tokens;
	int i;

	while (true)
	{
		printf("$ ");
		read = getline(&buffer, &len, stdin);
		if (read == -1)
		{
			free(buffer);
			return (0);
		}
		else if (buffer != NULL)
		{
			tokens = split_strings(buffer, delim);
			for (i = 0; tokens[i] != NULL; i++)
			{
				printf("%s\n", tokens[i]);
				free(tokens[i]);
			}
			free(tokens);
		}
	free(buffer);
	buffer = NULL;
	}

	return (0);
}
