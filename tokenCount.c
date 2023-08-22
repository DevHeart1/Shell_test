#include "shell.h"

/**
 * count_token - Counts the tokenized inputs
 * @input: The command inputed by the user
 *
 * Return: The total number of count
 */

int count_token(char *input)
{
	int Tcount = 0;

	char *token = strtok(input, " ");

	while (token != NULL)
	{
		Tcount++;
		token = strtok(NULL, " ");
	}
	return (Tcount);
}
