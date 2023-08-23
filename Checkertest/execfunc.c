#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>



/**
 * contains_path - checks if a string contains a '/'
 * @exec: the string to check
 * Return: 1 if '/' is found, 0 otherwise
 */
/*int contains_path(char *exec)
  {
  int q = 0;

  for (q = 0; exec[q] != '\0'; q++)
  {
  if (exec[q] == '/')
  {
  break;
  }
  }
  }*/

/**
 * display_Prompt - This function prints prompt to stdout
 *
 * Return: void
 */

void display_Prompt(void)
{
	char prompt[] = "#cisfun$ ";
	write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * count_token - Counts the tokenized inputs
 * @input: The command inputed by the user
 *
 * Return: The total number of tokens
 */

int count_token(char *input)
{
	int Tcount = 0;
	char *token = strtok(input, " ");

	while (token != NULL)
	{
		Tcount++;
		token = strtok(NULL, " ");
	}
	return (Tcount);
}

/**
 * Tokenize_Input - Function that tokenizes inputs from user
 * @input: The command inputed by user
 * @av: The argument vector array
 * @count: The number of tokens counted
 *
 * Return: void
 */

void Tokenize_Input(char *input, char **av, int count)
{
	int q;
	char *Token = strtok(input, " ");

	for (q = 0; q < count; q++)
	{
		av[q] = malloc(strlen(Token) + 1);
		strcpy(av[q], Token);
		Token = strtok(NULL, " ");
	}
	av[count] = NULL;
}

/* Function to check if a command contains a path */
int contains_path(const char *command) {
	return strchr(command, '/') != NULL;
}

/* Function to find the full path of the executable */
/*
char *find_full_path(const char *exec) {
	char *path_value = getenv("PATH");
	char *path_copy = strdup(path_value);
	char *path_token = strtok(path_copy, ":");

	struct stat stv;
	char *fullpath = NULL;

	while (path_token != NULL) {
		fullpath = malloc(strlen(path_token) + strlen(exec) + 2);

		if (fullpath == NULL) {
			perror("Memory Allocation failed");
			exit(EXIT_FAILURE);
		}

		strcpy(fullpath, path_token);
		strcat(fullpath, "/");
		strcat(fullpath, exec);

		if (stat(fullpath, &stv) == 0) {
			break;
		}

		free(fullpath);
		fullpath = NULL;
		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return fullpath;
}*/


/* Function to execute the command */
void execute_command(char **av)
{
    char *exec = av[0], *Output = av[1];
    const char *not_found_message = ": not found\n";
    size_t m, q;

    if (contains_path(exec))
    {
        if (execve(exec, av, NULL) == -1)
	{
            for (m  = 0; exec[m] != '\0'; m++)
	    {
    i            write(STDOUT_FILENO, &exec[m], 1);
            }
	    putchar("49");
	    putchar("58");
	    putchar(" ");
	    for (q = 0, Output[q] != '\0'; q++)
	    {
	    	write(STDOUT_FILENO, &Output[q], 1);
	    } 
            write(STDOUT_FILENO, not_found_message, strlen(not_found_message));  // Print custom error message

            exit(EXIT_FAILURE);
        }
    } else {
        if (execve(exec, av, NULL) == -1) {  // Handle execve failure
            for (size_t i = 0; exec[i] != '\0'; i++) {
                write(STDOUT_FILENO, &exec[i], 1);  // Print character by character
            }
            write(STDOUT_FILENO, not_found_message, strlen(not_found_message));  // Print custom error message

            exit(EXIT_FAILURE);
        }
    }

    /* Free memory allocated for the av array */
    for (int q = 0; av[q] != NULL; q++) {
        free(av[q]);
    }
}


int main(int ac, char *av[])
{
	char *buff = NULL, *buffCopy = NULL;
	size_t length = 0;
	(void)ac;

	while (1)
	{
		int q;

		if (isatty(STDIN_FILENO))
		{
			display_Prompt();
		}
		ssize_t readline = getline(&buff, &length, stdin);
		if (readline == EOF)
			break;
		buff[readline - 1] = '\0';
		buffCopy = strdup(buff);

		if (strcmp(buff, "exit") == 0)
		{
			free(buffCopy);
		}
		if (!buffCopy)
		{
			perror("Memory Allocation failed");
			return (-1);
		}

		int Count_Token = count_token(buffCopy);
		char **av = malloc(sizeof(char *) * (Count_Token + 1));
		if (!av)
		{
			perror("Memory Allocation failed");
			return (-1);
		}

		Tokenize_Input(buff, av, Count_Token);
		pid_t pidv = fork();
		if (pidv < 0)
			perror("Error creating child process");
		else if (pidv == 0)
			execute_command(av);
		else
		{
			int status;
			wait(&status);
		}

		for (q = 0; av[q] != NULL; q++)
		{
			free(av[q]);
		}
		free(av);
		free(buffCopy);
	}

	free(buff);
	exit(0);
}
