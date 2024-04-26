#include "simple_shell.h"

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
	if (tokens == NULL || tokens[0] == NULL || tokens[0][0] == '\0')
	{
		return (0); /*Tokens es NULL*/
	}
	return (check_command_access(tokens, env)); /*Token no es NULL*/
}

/**
 * check_command_access - Verifies and returns
 * the executable path of a command.
 *
 * @cmd: Pointer to the command input by the user.
 *
 * @env: Array of environment variables.
 *
 * Description: Checks if the command is an absolute
 * or relative path and verifies
 * its accessibility.
 * If not a path, it searches for the command in the system's PATH.
 * Returns 127 if the command cannot be found or is not executable.
 *
 * Return: On success, returns the exit status of the command or error code.
 */

int check_command_access(char **cmd, char **env)
{
	char *path;

	if (*cmd[0] == '/' || (*cmd[0] == '.' && (*cmd)[1] == '/')) /*'/' o './'*/
	{
		if (access(*cmd, X_OK) != 0) /*verificación de si existe y es ejecutable*/
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", *cmd); /*no existe o no es ejecutable*/
			return (127);
		}
		path = strdup(*cmd); /*si existe y es ejecutable, será el path de execve*/
	}
	else /* no es una ruta*/
	{
		path = search_in_path(*cmd, env);
		if (path == NULL)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", *cmd);
			return (127);
		}
	}
	return (execute_child_process(cmd, env, path));
}

/**
 * execute_child_process - Executes a command in a child process.
 *
 * @cmd: Command to execute.
 *
 * @env: Environment variables.
 *
 * @path: Path to the executable.
 *
 * Description: Forks a child process to execute a command.
 * It waits for the command
 * to terminate and returns its exit status.
 * If the command is terminated by a signal,
 * it adjusts the exit status accordingly.
 *
 * Return: Exit status of the command or adjusted signal exit status.
 */

int execute_child_process(char **cmd, char **env, char *path)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error en fork");
		free(path);
		return (1);
	}
	else if (pid == 0)
	{
		execve(path, cmd, env);
		perror("Error en execve");
		free(path);
		exit(127);
	}
	free(path);
	wait(&status);
	if (WIFEXITED(status)) /*verificar si hijo termino correctamente*/
		return (WEXITSTATUS(status)); /*obtener el codigo de salida del hijo*/
	else if (WIFSIGNALED(status)) /*hijo termino por un error*/
		return (128 + WTERMSIG(status)); /*obtener el código de salida del hijo cuando termina por error*/
	return (0);
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
	char *path = _getenv("PATH", env), *path_copy, *dir, *full_path, *result;
	size_t cmd_len, dir_len;

	if (!path)
	{
		return (NULL);
	}
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')) /*borrar*/
	{
		result = check_direct_access(cmd);
		if (result)
			return (result);
	}
	path_copy = strdup(path);
	if (!path_copy) /*la copia no salio*/
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	cmd_len = strlen(cmd);
	for (dir = strtok(path_copy, ":"); dir; dir = strtok(NULL, ":"))
	{
		dir_len = strlen(dir);
		full_path = malloc(dir_len + 1 + cmd_len + 1); /*dir, '/', cmd*/
		if (!full_path) /*es nulo*/
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, cmd); /*creando el full_path*/
		if (access(full_path, X_OK) == 0) /*full_path existe y es ejecutable*/
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
	}
	free(path_copy);
	return (NULL);
}

/**
 * check_direct_access - Checks if a command
 * is a direct path and is executable.
 *
 * @cmd: Command to check.
 *
 * Return: Copied string of path if executable, NULL otherwise.
 */

char *check_direct_access(const char *cmd) /*eliminar*/
{
	if (access(cmd, X_OK) == 0)
		return (strdup(cmd));
	return (NULL);
}
