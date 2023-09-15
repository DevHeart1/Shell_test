#include "shell.h"

void builtin(char *buff)
{
	if (_strcmp(buff, "exit") == 0)
	{
		exit(0);
	}
	else if (_strcmp(buff, "env") == 0)
	{
		if (isatty(1))
		{
			_env();
		}
	}
}

int _env(void)
{
	int i;
	char **_environ;

	for (i = 0; environ[i]; i++)
		;
	_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
		_environ[i] = _strdup(environ[i]);
	_environ[i] = NULL;

	for (i = 0; _environ[i]; i++)
	{
		write(STDOUT_FILENO, _environ[i], _strlen(_environ[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
