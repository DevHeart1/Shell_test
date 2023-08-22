#include "shell.h"

/**
 * display_Prompt - This function prints prompt to stdout
 *
 * Return: void
 */

void display_Prompt(void)
{
	char prompt[] = "#cisfun$ ";

	write(STDOUT_FILENO, prompt, strlen(prompt));
}
