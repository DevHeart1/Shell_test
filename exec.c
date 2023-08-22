#include "shell.h"


/**
 * executes_commands - function that executes command
 * @av: argument vector array
 *
 * Return: (0) on success
 */

int executes_commands(char **av)
{
	char *exec = av[0];
	int contains_path = 0, q = 0;

	for (q = 0; exec[q] != '\0'; q++)
	{
		if (exec[q] == '/')
		{
			contains_path = 1;
			break;
		}
	}

	if (contains_path)
	{
		if (execve(exec, av, NULL) == -1)
		{
			perror(exec);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		char *path_value = NULL;
		char *path_copy = NULL;
		char *path_token = NULL;
		struct stat stv;
		char *fullpath;
		int found = 0;

		path_value = getenv("PATH");
		path_copy = strdup(path_value);

		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			fullpath = malloc(strlen(path_token) + strlen(exec) + 2);

			if (fullpath == NULL)
			{
				perror("Memory Allocation failed");
				exit(EXIT_FAILURE);
			}
			strcpy(fullpath, path_token);
			strcat(fullpath, "/");
			strcat(fullpath, exec);

			if (stat(fullpath, &stv) == 0)
			{
				found = 1;
				break;
			}
			free(fullpath);
			path_token = strtok(NULL, ":");
		}

		free(path_copy);

		if (found)
		{
			if (execve(fullpath, av, NULL) == -1)
			{
				perror(fullpath);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			perror(exec);
			exit(EXIT_FAILURE);
		}

		/* Free fullpath after it's no longer needed */
		free(fullpath);
	}

	/* Free memory allocated for the av array */
	for (q = 0; av[q] != NULL; q++)
	{
		free(av[q]);
	}

}
