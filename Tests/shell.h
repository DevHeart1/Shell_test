#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;
void Tokenize_Input(char *input, char **av, int count);
void display_Prompt(void);
int count_token(char *input);
int executes_commands(char **av);
void handle_child_process(pid_t pidv, char **av);
void process_input(char *buff);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
size_t _strlen(const char *s);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
void _memcpy(void *dest, const void *src, unsigned int size);
char *_getenv(const char *name);
int _strncmp(const char *s1, const char *s2, size_t n);


#endif
