#include "shell.h"

void Tokenize_Input(char *input, char **av, int count)
{
	int q;
	char *Token = strtok(input, " ");

	for (q = 0; q < count; q++)
	{
		av[q] = malloc(strlen(Token) + 1);
		if (!av[q])
		{
            	perror("Memory allocation failed");
            	exit(EXIT_FAILURE);
        	}
		strcpy(av[q], Token);
		Token = strtok(NULL, " ");
	}
	av[count] = NULL;
}

void display_Prompt(void)
{
	char prompt[] = "#cisfun$ ";
	write(STDOUT_FILENO, prompt, strlen(prompt));
}

int count_token(char *input)
{
	int Tcount = 0;
	char *token = strtok(input, " ");
	while (token != NULL)
	{
		Tcount++;
		token = strtok(NULL, " ");
	}
	return Tcount;
}

/**
 * _memcpy - copies data to another pointer with casts
 * @dest: dest to paste data
 * @src: source to copy data from
 * @size: length of data to copy
 * Return: nothing
 */
void _memcpy(void *dest, const void *src, unsigned int size)
{
	char *ptr = (char *)src;
	char *new = (char *)dest;
	unsigned int i;

	for (i = 0; i < size; i++)
		new[i] = ptr[i];
}
