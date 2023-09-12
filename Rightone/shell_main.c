#include "shell.h"

/**
 * handle_child_process - Handle child process execution
 * @pidv: PID of the child process
 * @av: Array of command arguments
 */
int handle_child_process(pid_t pidv, char **av, char *argv)
{
    if (pidv < 0)
    {
        perror("Error creating child process");
        return (-1);
    }
    else if (pidv == 0)
    {
        int sta;

        sta = executes_commands(av, argv);
        exit(sta); /*Exit the child process with the status of executes_commands*/
    }
    else
    {
        int wait_status;

        if (wait(&wait_status) == -1)
        {
            perror("Error waiting for child process");
            return (-1);
        }
        /*Check if the child process exited normally*/
        if (WIFEXITED(wait_status))
        {
            return WEXITSTATUS(wait_status); /*Return the exit status of the child process*/
        }
        else
        {
            /* Handle cases where the child process didn't exit normally*/
            return (-1);
        }
    }
}


/**
 * process_input - Process user input
 * @buff: User input buffer
 */
int process_input(char *buff, char *argv)
{
	int q, Count_Token, status;
	char **av;
	char *buffCopy;
	pid_t pidv;

	buff[_strlen(buff) - 1] = '\0';
	buffCopy = _strdup(buff);

	if (!buffCopy)
	{
		perror("Memory Allocation failed");
		exit(-1);
	}

	builtin(buffCopy);

	Count_Token = count_token(buffCopy);
	av = malloc(sizeof(char *) * (Count_Token + 1));

	if (!av)
	{
		perror("Memory Allocation failed");
		exit(-1);
	}

	Tokenize_Input(buff, av, Count_Token);
	pidv = fork();
	
	status = handle_child_process(pidv, av, argv);

	for (q = 0; q < Count_Token; q++)
	{
		free(av[q]);
	}
	free(av);
	free(buffCopy);
	return (status);
}

/**
 * main - Entry point
 * @ac: Argument count
 * @av: Argument vector
 * Return: 0 on success, non-zero on failure
 */
int main(int ac, char *av[])
{
	int status, stv = 0;
	char *buff = NULL;
	size_t length = 0;
	ssize_t readline;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			display_Prompt();
		}

		readline = getline(&buff, &length, stdin);

		if (readline == EOF)
		{
			break;
		}
		status = process_input(buff, av[0]);
		if (status != 0)
		{
			stv = status;
			continue;
		}
	}
	free(buff);
	return (stv);
}
