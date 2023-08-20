#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


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
