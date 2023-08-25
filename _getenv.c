#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *_getenv(const char *name)
{
	extern char **environ;
	int q = 0;
	char *token;

	while (environ[q])
	{
		token = strtok(environ[q], "=");
		if (strcmp(token, name) == 0)
		{
			return (strtok(NULL, "="));
		}
		q++;
	}
	return (NULL);
}

int main(void)
{
	char *path = _getenv("PATH");
	printf("%s\n", path);
}
