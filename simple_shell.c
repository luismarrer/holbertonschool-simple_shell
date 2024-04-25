#include "simple_shell.h"

/**
 * main - This program is a simple shell.
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
		tokens = split_strings(buffer, delim);
		if (tokens && tokens[0])
		{
			if (strcmp(tokens[0], "exit") == 0)
			{
				free_memory(tokens, buffer);
				exit(last_command_status);
			}
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
 * execute_command - It is an auxiliary function that
 * calls the commands to be executed.
 *
 * @tokens: Command to execute.
 *
 * @env: The environment variables.
 *
 * Return: 0 on successful execution of a command,
 * nonzero if the command execution fails or if there is an error.
 */

int execute_command(char **tokens, char **env)
{
	pid_t pid;
	int status;
	char *path;

	if (tokens == NULL || tokens[0] == NULL || tokens[0][0] == '\0')
		return (0);
	path = search_in_path(tokens[0]);
	if (path == NULL)
	{
		fprintf(stderr, "%s: command not found\n", tokens[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Error en fork");
		free(path);
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(path, tokens, env) == -1)
		{
			perror("Error en execve");
			exit(127);
		}
	}
	else
	{
		wait(&status);
		free(path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (0);
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
}

/**
 * search_in_path - Searches for an executable in the system PATH.
 *
 * @cmd: The command to search for.
 *
 * Return: A pointer to a string containing the full path
 * of the command if found,
 * NULL if the command is not found.
 */

char *search_in_path(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir;
	char *full_path;
	size_t cmd_len = strlen(cmd);
	size_t dir_len;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		return (strdup(cmd));
	}

	if (!path_copy)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	for (dir = strtok(path_copy, ":"); dir != NULL; dir = strtok(NULL, ":"))
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + 1 + cmd_len + 1);
		if (!full_path)
		{
			perror("Failed to allocate memory");
			free(path_copy);
			return (NULL);
		}
		strcpy(full_path, dir);
		full_path[dir_len] = '/';
		strcpy(full_path + dir_len + 1, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
	}
	free(path_copy);
	return (NULL);
}
