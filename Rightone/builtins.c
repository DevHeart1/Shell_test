#include "shell.h"

void builtin(char *buff)
{
    int idx = 0;

    if (_strcmp(buff, "exit") == 0)
	{
		free(buff);
		exit(0);
	}
    else if (_strcmp(buff, "exit") == 0)
    {
        free(buff);
        exit(2);
    }
	else if (_strcmp(buff, "env") == 0)
	{
		if (isatty(1))
		{
			while (environ[idx] != NULL)
			{
				write(1, environ[idx], _strlen(environ[idx]));
				write(1, "\n", 1);

				idx++;
			}
        }
    }
}