#include "shell.h"

int contains_path(char *exec)
{
	for (int q = 0; exec[q] != '\0'; q++)
	{
		if (exec[q] == '/')
		{
			return (1);
		}
	}
	return (0);
}

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
	return (fullpath);
}

char *search_executable_in_path(char *exec, char *path_value)
{
	char *path_copy = _strdup(path_value);
	char *path_token = strtok(path_copy, ":");
	char *fullpath = NULL;

	while (path_token != NULL)
	{
		fullpath = get_full_path(exec, path_token);
		struct stat stv;
		if (stat(fullpath, &stv) == 0)
		{
			break;
		}
		free(fullpath);
		fullpath = NULL;
		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return (fullpath);
}

int executes_commands(char **av)
{
	char *exec = av[0];

	if (contains_path(exec))
	{
		if (execve(exec, av, NULL) == -1)
		{
			perror(exec);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		char *path_value = _getenv("PATH");
		char *fullpath = search_executable_in_path(exec, path_value);

		if (fullpath)
		{
			if (execve(fullpath, av, NULL) == -1)
			{
				perror(fullpath);
				exit(EXIT_FAILURE);
			}
			free(fullpath);
		}
		else
		{
			perror(exec);
			exit(EXIT_FAILURE);
		}
		
	}
	return 0;
}
