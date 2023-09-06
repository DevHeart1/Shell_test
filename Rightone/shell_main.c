#include "shell.h"

/**
 * handle_child_process - Handle child process execution
 * @pidv: PID of the child process
 * @av: Array of command arguments
 */
void handle_child_process(pid_t pidv, char **av)
{
	if (pidv < 0)
	{
		perror("Error creating child process");
	}
	else if (pidv == 0)
	{
		executes_commands(av);
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		if (wait(&status) == -1)
		{
			perror("Error waiting for child process");
		}
	}
}

/**
 * process_input - Process user input
 * @buff: User input buffer
 */
void process_input(char *buff)
{
	int q, Count_Token;
	char **av;
	pid_t pidv;

	buff[_strlen(buff) - 1] = '\0';
	char *buffCopy = _strdup(buff);

	if (!buffCopy)
	{
		perror("Memory Allocation failed");
		exit(-1);
	}

	if (_strcmp(buffCopy, "exit") == 0)
	{
		free(buffCopy);
		exit(0);
	}

	Count_Token = count_token(buffCopy);
	av = malloc(sizeof(char *) * (Count_Token + 1));
	if (!av)
	{
		perror("Memory Allocation failed");
		exit(-1);
	}

	Tokenize_Input(buff, av, Count_Token);
	pidv = fork();
	handle_child_process(pidv, av);
	
	for (q = 0; q < Count_Token; q++)
	{
		free(av[q]);
	}
	free(av);
	free(buffCopy);
}

/**
 * main - Entry point
 * @ac: Argument count
 * @av: Argument vector
 * Return: 0 on success, non-zero on failure
 */
int main(int ac, char *av[])
{
	char *buff = NULL;
	size_t length = 0;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			display_Prompt();
		}

		ssize_t readline = getline(&buff, &length, stdin);

		if (readline == EOF)
		{
			break;
		}
		process_input(buff);
	}

	free(buff);
	return (0);
}
