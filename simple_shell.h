#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/*libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

/*simple_shell*/
char **split_strings(const char *input, const char *delims);
void free_memory(char **tokens, char *buffer);
/*execute_command*/
int execute_command(char **tokens, char **env);
int check_command_access(char **cmd, char **env);
int execute_child_process(char **cmd, char **env, char *path);
char *search_in_path(char *cmd, char **env);
char *check_direct_access(const char *cmd);
/*env*/
void print_environment(char **env);
/*my_own_func*/
void *_realloc(void *ptr, size_t old_size, size_t new_size);
char *_getenv(const char *name, char **env);

#endif
