#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * Tokenize_Input - Function that tokenize inputs from user
 * @input: the command inputed by user
 * @av: The argument vector array
 * @count: The number of tokens counted
 *
 * Return: void
 */

void Tokenize_Input(char *input, char **av, int count)
{
	int q;
	char *Token = strtok(input, " ");

	for (q = 0; q < count; q++)
	{
		av[q] = malloc(strlen(Token) + 1);
		strcpy(av[q], Token);
		Token = strtok(NULL, " ");
	}
	av[count] = NULL;
}
