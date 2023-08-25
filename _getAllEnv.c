#include "shell.h"

/**
 * _getenv - Function that Gets environment variable.
 * @name: Variable to look for
 *
 * Return: The environnment variable, or NULL if not found
 */

char *_getenv(const char *name)
{
	int q = 0, p, count = 0, len;
	char *dup = (char *)name;

	if (name == NULL || !name[q])
		return (NULL);

	len = _strlen(dup);
	while (*(environ + q))
	{
		p = 0;
		while (*(*(environ + q) + p) != '=')
		{
			if (*(*(environ + q) + p) == name[p])
				count++;
			p++;
		}
		if (count == len)
		{
			p++;
			return (*(environ + q) + p);
		}
		q++;
		count = 0;
	}
	return (NULL);
}
