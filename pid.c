#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */

int main(void)
{
	pid_t child_pid;
	pid_t parent_pid = getppid();

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Error");
		exit(1);
	}

	if (child_pid == 0)
	{
		printf("I am the child process. my id is %u\n", child_pid);
	}
	else
	{
		wait(NULL);
	 	printf("I am the parent process. My pid is %u\n", parent_pid);
	}

	return (0);
}
