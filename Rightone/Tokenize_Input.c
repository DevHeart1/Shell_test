#include "shell.h"

/**
 * Tokenize_Input - Tokenizes input string into an array of tokens
 * @input: The input string to tokenize
 * @av: An array to store the tokens
 * @count: The number of tokens to tokenize
 */
void Tokenize_Input(char *input, char **av, int count)
{
    int q;
    char *Token = _strtok(input, " ");

    for (q = 0; q < count; q++)
    {
        av[q] = malloc(_strlen(Token) + 1);
        _strcpy(av[q], Token);
        Token = _strtok(NULL, " ");
    }
    av[count] = NULL;
}

/**
 * display_Prompt - Displays the shell prompt
 */
void display_Prompt(void)
{
    char prompt[] = "#cisfun$ ";
    write(STDOUT_FILENO, prompt, _strlen(prompt));
}

/**
 * count_token - Counts the number of tokens in a string
 * @input: The input string
 * Return: The number of tokens
 */
int count_token(char *input)
{
    int Tcount = 0;
    char *token = _strtok(input, " ");
    while (token != NULL)
    {
        Tcount++;
        token = _strtok(NULL, " ");
    }
    return (Tcount);
}

/**
 * _strncmp - Compares two strings up to n bytes.
 * @s1: First string.
 * @s2: Second string.
 * @n: Number of bytes to compare.
 * Return: The difference between the two strings.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 == '\0' && *s2 == '\0')
		{
			return (0);
		}
		else if (*s1 == *s2)
		{
			s1++;
			s2++;
			n--;
		}
		else
		{
			return (*s1 - *s2);
		}
	}
	return (0);
}
