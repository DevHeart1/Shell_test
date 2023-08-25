#include "shell.h"

char *_getenv(const char *name)
{
    int q = 0, p, count = 0, len;
    char *dup = (char *)name;
	char **environ;

    if (name == NULL || !name[q])
        return (NULL);

    len = strlen(dup);
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

int main(void)
{
        char *path = _getenv("PATH");
        printf("%s\n", path);
}
