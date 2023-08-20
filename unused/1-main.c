#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * display_Prompt - This function prints prompt to stdout
 *
 * Return: void
 */

void display_Prompt(void)
{
	char prompt[] = "#cisfun$";

	write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * count_token - Counts the tokenized inputs
 * @input: The command inputed by the user
 *
 * Return: The total number of count
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
 * Tokenize_Input - Function that tokenize inputs from user
 * @input: the command inputed by user
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

/**
 * executes_commands - function that executes command
 * @av: argument vector array
 *
 * Return: (0) on success
 */
int executes_commands(char **av)
{
	char *exec = av[0];

	if (execve(exec, av, NULL) == -1)
	{
		perror("./shell");
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * main - main entry point
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: (0) on success
 */

int main(int ac, char *av[])
{
	ssize_t readline;
	size_t length = 0;
	char *buff = NULL, *buffCopy = NULL;
	pid_t pidv;
	(void)ac;

	while (1)
	{
		int Count_Token;

		display_Prompt();
		readline = getline(&buff, &length, stdin);
		if (readline == EOF)
			break;
		buff[readline - 1] = '\0';

		buffCopy = malloc(sizeof(char) * readline + 1);
		if (buffCopy == NULL)
		{
			perror("Memory Allocation failed");
			return (-1);
		}
		strcpy(buffCopy, buff);
		Count_Token = count_token(buffCopy);
		av = malloc(sizeof(char *) * (Count_Token + 1));
		if (av == NULL)
		{
			perror("Memory Allocation failed");
			return (-1);
		}
		Tokenize_Input(buff, av, Count_Token);
		pidv = fork();
		if (pidv < 0)
			perror("Error creating child process");
		else if (pidv == 0)
		{
			executes_commands(av);
		}
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
