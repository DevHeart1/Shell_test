#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

void Tokenize_Input(char *input, char **av, int count);
void display_Prompt(void);
int count_token(char *input);
int executes_commands(char **av);
void handle_child_process(pid_t pidv, char **av);
void process_input(char *buff);

#endif
