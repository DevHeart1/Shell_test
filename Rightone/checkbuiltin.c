#include "shell.h"

/**
 * is_exit - Checks if the given token is "exit" and handles the exit status
 * @token: The token to check if it is "exit".
 * @status: The optional argument for the exit status.
 * Return: nothing
 */
void is_exit(char *token, char *status)
{
	int exit_arg;
	size_t i, length;

	if (_strcmp("exit", token) == 0)
	{
		/* Check if an argument (status) is provided */
		if (status == NULL)
		{
			exit(0); /* No status argument provided, exit with status 0 */
		}
		else
		{
			/* check if status argument contains only digits */
			length = _strlen(status);
			for (i = 0; i < length; i++)
			{
				if (!_isdigit(status[i]))
				{
					illegal_status(token, 1, status);
					exit(2);
				}
			}
			/* Convert the status argument to an integer */
			exit_arg = _atoi(status);
			exit(exit_arg);
		}
	}
}
