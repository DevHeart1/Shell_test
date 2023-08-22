#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * display_Prompt - This function prints prompt to stdout
 *
 * Return: void
 */

void display_Prompt(void)
{
	char prompt[] = "#cisfun$ ";
	write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * count_token - Counts the tokenized inputs
 * @input: The command inputed by the user
 *
 * Return: The total number of tokens
 */

int count_token(char *input)
{
	int Tcount = 0;
	char *token = strtok(input, " ");

	while (token != NULL)
	{
		Tcount++;
		token = strtok(NULL, " ");
	}
	return (Tcount);
}

/**
 * Tokenize_Input - Function that tokenizes inputs from user
 * @input: The command inputed by user
 * @av: The argument vector array
 * @count: The number of tokens counted
 *
 * Return: void
 */

void Tokenize_Input(char *input, char **av, int count)
{
	int q;
	char *Token = strtok(input, " ");

	for (q = 0; q < count; q++)
	{
		av[q] = malloc(strlen(Token) + 1);
		strcpy(av[q], Token);
		Token = strtok(NULL, " ");
	}
	av[count] = NULL;
}

void execute_command(char **av)
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

int main(int ac, char *av[])
{
	char *buff = NULL, *buffCopy = NULL;
	size_t length = 0;
	(void)ac;

	while (1)
	{
		display_Prompt();
		ssize_t readline = getline(&buff, &length, stdin);
		if (readline == EOF)
			break;
		buff[readline - 1] = '\0';

		buffCopy = strdup(buff);
		if (!buffCopy)
		{
			perror("Memory Allocation failed");
			return (-1);
		}

		int Count_Token = count_token(buffCopy);
		char **av = malloc(sizeof(char *) * (Count_Token + 1));
		if (!av)
		{
			perror("Memory Allocation failed");
			return (-1);
		}

		Tokenize_Input(buff, av, Count_Token);
		pid_t pidv = fork();
		if (pidv < 0)
			perror("Error creating child process");
		else if (pidv == 0)
			execute_command(av);
		else
		{
			int status;
			wait(&status);
		}

		free(av);
		free(buffCopy);
	}

	free(buff);
	return (0);
}
