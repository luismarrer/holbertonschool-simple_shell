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
	char *path = NULL;

	if (tokens == NULL || tokens[0] == NULL || tokens[0][0] == '\0')
		return (0);
	if (tokens[0][0] == '/' || (tokens[0][0] == '.' && tokens[0][1] == '/'))
	{
		if (access(tokens[0], X_OK) != 0)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", tokens[0]);
			return (127);
		}
		path = strdup(tokens[0]);
	}
	else
	{
		path = search_in_path(tokens[0], env);
		if (path == NULL)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", tokens[0]);;
			return (127);
		}
	}
	pid = fork();
	if (pid == -1)
	{
		free(path);
		return (1);
	}
	if (pid == 0)
	{
		execve(path, tokens, env);
		exit(127);
	}
	free(path);
	wait(&status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
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
 * @env: Environment variables array.
 *
 * Description: If the command starts with '/' or './', the function
 * assumes it is an absolute or relative path and checks its existence.
 * Otherwise, it searches the command in directories specified in PATH.
 *
 * Return: A dynamically allocated string containing the full path to the
 * command if found, NULL otherwise.
 */

char *search_in_path(char *cmd, char **env)
{
	char *path = _getenv("PATH", env), *path_copy, *dir, *full_path;
	size_t cmd_len, dir_len;

	if (!path)
	{
		return (NULL);
	}
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			return (strdup(cmd));
		}
		return (NULL);
	}
	path_copy = strdup(path);
	if (!path_copy)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	cmd_len = strlen(cmd);
	for (dir = strtok(path_copy, ":"); dir; dir = strtok(NULL, ":"))
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + 1 + cmd_len + 1);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd);
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

