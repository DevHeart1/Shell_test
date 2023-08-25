#include "shell.h"

/**
 * Display_Environ_Var - Function that prints environment variable
 * 
 *
 */

void Display_Environ_Var(void)
{
	extern char **Environment;

	for (char **env = Environment; *env != NULL; env++)
	{
		write(STDIO_FILENO, Environment, strlen(Environment));
	}
}

