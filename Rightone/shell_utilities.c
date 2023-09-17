#include "shell.h"

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: pointer to the resulting string dest
 */
char *_strcat(char *dest, const char *src)
{
	int i, len = _strlen(dest);

	for (i = 0; src[i] != '\0'; i++)
		dest[len + i] = src[i];
	dest[len + i] = src[i];
	return (dest);
}


/**
 * _strcpy - copies the string pointed to by src to dest
 * @dest: destination string
 * @src: source string
 * Return: pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = src[i];
	return (dest);
}

/**
 * _strlen - returns the length of a string
 * @s: string to be measured
 * Return: length of the string
 */
size_t _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != '\0'; len++)
		;
	return (len);
}

/**
 *_strcmp - function that compare two string
 *@s1: The first string to compare
 *@s2: The second string to compare
 *Return: s1 - s2
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] && s2[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i]  - s2[i]);
		}
	}
	return (s1[i] - s2[i]);
}

/**
 * _strdup - duplicates a string, allocating the appropriate size to the copy
 * @str: to be duplicated
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(char *str)
{
	char *dup;
	size_t len;

	len = _strlen(str);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	_memcpy(dup, str, len + 1);
	return (dup);
}
