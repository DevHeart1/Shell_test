#include "shell.h"

/**
 * main - main entry point
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: (0) on success
 */

#include "shell.h"

int main(int ac, char *av[])
{
	char *buff = NULL, *buffCopy = NULL;
	size_t length = 0;
	(void)ac;

	while (1)
	{
		display_Prompt();
		ssize_t readline = getline(&buff, &length, stdin);
		if (readline == EOF) break;
		buff[readline - 1] = '\0';

		buffCopy = strdup(buff);
		if (!buffCopy) { perror("Memory Allocation failed"); return (-1); }

		int Count_Token = count_token(buffCopy);
		char **av = malloc(sizeof(char *) * (Count_Token + 1));
		if (!av) { perror("Memory Allocation failed"); return (-1); }

		Tokenize_Input(buff, av, Count_Token);
		pid_t pidv = fork();
		if (pidv < 0) perror("Error creating child process");
		else if (pidv == 0) executes_commands(av);
		else { int status; wait(&status); }

		free(av);
		free(buffCopy);
	}

	free(buff);
	return (0);
}

