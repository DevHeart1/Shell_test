#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include  <sys/stat.h>

int count_token(char *input);
void Tokenize_Input(char *input, char **av, int count);
void display_Prompt(void);
void second_Prompt(void)
int executes_commands(char **av);

#endif
