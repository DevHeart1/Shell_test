#include "shell.h"

/**
 * _strtok - Tokenize a string based on delimiters.
 * @str: The string to tokenize.
 * @delimiters: A string containing delimiter characters.
 *
 * Return: A pointer to the next token or NULL if no more tokens are found.
 */

char *_strtok(char *str, const char *delimiters)
{
	static char *end_str;
	char *TokenS = end_str;

	if (str != NULL)
		end_str = str;

	if (end_str == NULL)
		return (NULL);

	while (*end_str != '\0' && strchr(delimiters, *end_str) != NULL)
		end_str++;

	if (end_str == '\0')
	{
		end_str = NULL;
		return (NULL);
	}

	while (*end_str != '\0' && strchr(delimiters, *end_str) == NULL)
		end_str++;

	if (*end_str != '\0')
	{
		*end_str = '\0';
		end_str++;
	}
	else
	{
		end_str = NULL;
	}
	return (TokenS);
}
