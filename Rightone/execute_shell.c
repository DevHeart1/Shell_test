#include "shell.h"

/**
 * contains_path - Check if the executable contains a path.
 * @exec: The executable to check.
 *
 * Return: 1 if the executable contains a path, 0 otherwise.
 */
int contains_path(char *exec)
{
	int q;

	for (q = 0; exec[q] != '\0'; q++)
	{
		if (exec[q] == '/')
		{
			return 1;
		}
	}
	return 0;
}

/**
 * get_full_path - Get the full path of an executable.
 * @exec: The name of the executable.
 * @path_token: The path token to prepend.
 *
 * Return: The full path of the executable.
 */
char *get_full_path(char *exec, char *path_token)
{
	char *fullpath = malloc(_strlen(path_token) + _strlen(exec) + 2);
	if (!fullpath)
	{
		perror("Memory Allocation failed");
		exit(EXIT_FAILURE);
	}
	_strcpy(fullpath, path_token);
	_strcat(fullpath, "/");
	_strcat(fullpath, exec);
	return fullpath;
}

/**
 * search_executable_in_path - Search for an executable in the PATH environment variable.
 * @exec: The name of the executable.
 * @path_value: The PATH environment variable value.
 *
 * Return: The full path of the executable if found, NULL otherwise.
 */
char *search_executable_in_path(char *exec, char *path_value)
{
	char *path_copy = _strdup(path_value);
	char *path_token = strtok(path_copy, ":");
	char *fullpath = NULL;
	struct stat stv;

	while (path_token != NULL)
	{
		fullpath = get_full_path(exec, path_token);
		if (stat(fullpath, &stv) == 0)
		{
			break;
		}
		free(fullpath);
		fullpath = NULL;
		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return fullpath;
}

/**
 * executes_commands - Execute a command with or without a path.
 * @av: An array of command arguments.
 *
 * Return: Always returns 0.
 */
int executes_commands(char **av, char *argv)
{
	char *exec = av[0];
	int count = 1, status = 0, status_2 = 127;

	if (contains_path(exec))
	{
		if (execve(exec, av, environ) == -1)
		{
			_error(argv, count, exec);
			return (status_2);
		}
	}
	else
	{
		char *path_value = _getenv("PATH");
		char *fullpath = search_executable_in_path(exec, path_value);

		if (fullpath)
		{
			if (execve(fullpath, av, environ) == -1)
			{
				_error(argv, count, fullpath);
				return (status_2);
			}
			free(fullpath);
		}
		else
		{
			_error(argv, count, exec);
			return (status_2);
		}
	}
	
	return (status);
}
