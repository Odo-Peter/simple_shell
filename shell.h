#ifndef __SHELL_H__
#define __SHELL_H__

/* Libraries Inclusions*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Definitions for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* Definitions for chaining commands */
#define CMD_DEFAULT 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Definitions for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Conditionals for using system getline() */
#define USE_SYSTEM_GETLINE 0
#define USE_SYSTEM_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/****** Structures Definitions *******/
/**
 * struct liststring - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} list_t;

/**
 * struct info_to_be_passed - contains pseudo-arguements
 * to be passed into a functions,
 * @arg: a generated string from getline containing args
 * @argv:an string vector
 * @path: a path in string format for the current cmd
 * @argc: the args count
 * @line_count: the line count
 * @error_number: the error code to check (in use for exit()s)
 * @linecount_flag: flags attached to line counts
 * @file_name: the program filename
 * @env: linked list local copy from system environ
 * @environ: custom modified copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @env_changed: checks if environ variable changes
 * @status: the return status of the last executed command
 * @cmd_buffer: address of pointer to cmd_buffer
 * @cmd_buffer_type: CMD_type, either '||', '&&', ';'
 * @read_file_dir: the file directory from which to read line input from
 * @history_count: the history line number count
 */
typedef struct info_to_be_passed
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_number;
	int linecount_flag;
	char *file_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer;
	int cmd_buffer_type;
	int read_file_dir;
	int history_count;
} info_t;

/* INFO initialization definitions*/
#define INITIALIZE_INFO                                                         \
	{                                                                           \
	NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0                                                             \
		}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_t;

/* Functions for __shell_init.c */
int __h_shell(info_t *, char **);
int __find_builtins(info_t *);
void __find_commands(info_t *);
void __fork_command(info_t *);

/* Functions for __parse_func.c */
int __is_command(info_t *, char *);
char *__duplicate_chars(char *, int, int);
char *__path_finder(info_t *, char *, char *);

/* Functions for __errors_check.c */
void __error_puts(char *);
int __error_putchar(char);
int __put_file_desc(char c, int fd);
int __puts_file_desc(char *str, int fd);

/* Functions for __string_manip.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* Functions for __string_manip_two.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* Functions for __string_manip_three.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* Functions for __get_tokens.c */
char **__strtok_one(char *, char *);
char **__strtok_two(char *, char);

/* Functions for __mem_alloc.c */
char *_memset(char *, char, unsigned int);
void __f_free(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* Function for __mem_manip.c */
int __buff_free(void **);

/* Functions for __atoi.c */
int __is_interactive(info_t *);
int __is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* Functions for __error_handlers.c */
int _erratoi(char *);
void __p_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* Functions for __builtins_one.c */
int __exit(info_t *);
int __cd(info_t *);
int __help(info_t *);

/* Functions for __builtins_two.c */
int __history(info_t *);
int __alias(info_t *);

/*Functions for __get_lines.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void __handle_signals(int);

/* Functions for __info_getter.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Functions for __environs.c */
char *_getenv(info_t *, const char *);
int __env(info_t *);
int __setenv(info_t *);
int __unsetenv(info_t *);
int populate_env_list(info_t *);

/* Functions for __get_envs.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* Functions for __historia_reiss.c  :) */
char *__get_file_history(info_t *info);
int __write_history(info_t *info);
int __read_history(info_t *info);
int __build_history_list(info_t *info, char *buf, int linecount);
int __re_number_history(info_t *info);

/* Functions for __node_list_manip.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* Functions for __linked_list_manip.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_at_index(list_t *, list_t *);

/* Functions for __check_vars.c */
int __Is_chained(info_t *, char *, size_t *);
void __chain_checks(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
