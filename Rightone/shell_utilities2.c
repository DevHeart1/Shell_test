#include "shell.h"

/**
 * _memcpy - Copy data from source to destination.
 * @dest: Destination pointer.
 * @src: Source pointer.
 * @size: Number of bytes to copy.
 */
void _memcpy(void *dest, const void *src, unsigned int size)
{
	char *ptr = (char *)src;
	char *new = (char *)dest;
	unsigned int i;

	for (i = 0; i < size; i++)
		new[i] = ptr[i];
}

/**
 * _getenv - Get the value of an environment variable.
 * @name: Name of the environment variable.
 * Return: Pointer to the value of the environment variable,
 *         or NULL if not found.
 */
char *_getenv(const char *name)
{
	char **env;
	char *env_name, *delimeter;
	size_t name_len;

	if (name == NULL || name[0] == '\0')
		return (NULL);
	for (env = environ; *env != NULL; env++)
	{
		env_name = *env;
		delimeter = _strchr(env_name, '=');

		if (delimeter != NULL)
		{
			name_len = (size_t)(delimeter - env_name);
			if (_strlen(name) == name_len && _strncmp(env_name, name, name_len) == 0)
			{
				return (delimeter + 1);
			}
		}
	}
	return (NULL);
}

/**
 * _strchr - Locate character in string
 * @str: The string to search
 * @c: The character to locate
 *
 * Return: Pointer to the first occurrence of the character 'c' in 
 * the string 'str'.
 */
char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (char *)str;
		str++;
	}

	if (c == '\0')
		return (char *)str;

	return (NULL);
}

/**
 * _strtok - Tokenize a string based on delimiters.
 * @str: The string to tokenize.
 * @delimiters: A string containing delimiter characters.
 *
 * Return: A pointer to the next token or NULL if no more tokens are found.
 */
char *_strtok(char *str, const char *delimiters)
{
	static char *begin;
	char *Token_beginning = NULL;

	if (str != NULL)
		begin = str;

	if (begin == NULL || *begin == '\0')
		return (NULL);

	while (*begin != '\0' && _strchr(delimiters, *begin) != NULL)
		begin++;

	Token_beginning = begin;

	while (*begin != '\0' && _strchr(delimiters, *begin) == NULL)
		begin++;

	if (*begin != '\0')
	{
		*begin = '\0';
		begin++;
	}

	return (Token_beginning);
}
