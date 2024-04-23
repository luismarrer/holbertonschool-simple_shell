#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

char **split_strings(const char *input, const char *delims);
void execute_command(char **tokens, char **env);
void *_realloc(void *ptr, size_t old_size, size_t new_size);

#endif
