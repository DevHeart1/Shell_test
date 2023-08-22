#include "shell.h"

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

void process_input(char *buff)
{
	buff[strlen(buff) - 1] = '\0';
	char *buffCopy = strdup(buff);
	if (!buffCopy)
	{
		perror("Memory Allocation failed");
		exit(-1);
	}

	if (strcmp(buffCopy, "exit") == 0)
	{
		free(buffCopy);
		exit(0);
	}

	int Count_Token = count_token(buffCopy);
	char **av = malloc(sizeof(char *) * (Count_Token + 1));
	if (!av)
	{
		perror("Memory Allocation failed");
		exit(-1);
	}

	Tokenize_Input(buff, av, Count_Token);
	pid_t pidv = fork();
	handle_child_process(pidv, av);

	free(av);
	free(buffCopy);
}

int main(int ac, char *av[])
{
	char *buff = NULL;
	size_t length = 0;
	int Newline = 0;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			if (Newline)
			{
				write(STDOUT_FILENO, "\n", sizeof("\n") - 1);
			}
			display_Prompt();
		}
		else if(!isatty(STDIN_FILENO)) 
		{
			if (Newline)
				write(STDOUT_FILENO, "\n", sizeof("\n") - 1);
		}

		ssize_t readline = getline(&buff, &length, stdin);

		if (readline == EOF)
		{
			break;
		}

		process_input(buff);
		display_Prompt();
		Newline = 1;
	}

	free(buff);
	exit(0);
}
