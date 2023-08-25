#include "shell.h"

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be checked.
 * @c: The character to be located.
 * Return: A pointer to the first occurence if c is found else NULL
 */

char *_strchr(char *s, char c)
{
	int length = 0;

	while (s[length] >= '\0')
	{
		if (s[length] == c)
		{
			return (s + length);
		}
		length++;
	}
	return ('\0');
}
