#include "shell.h"

void Tokenize_Input(char *input, char **av, int count)
{
	int q, m, Index;
	char *Token = strtok(input, " ");

	for (q = 0; q < count; q++)
	{
		av[q] = malloc(strlen(Token) + 1);
		if (!av[q])
		{
			for (m = 0; m < q; m++)
			{
                		free(av[m]);
            		}
            	perror("Memory allocation failed");
            	exit(EXIT_FAILURE);
        	}
		strcpy(av[q], Token);
		Token = strtok(NULL, " ");
	}
	av[count] = NULL;
	for (Index = 0; Index < count; Index++)
	{
        	free(av[Index]);
    	}
	free(av);
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
