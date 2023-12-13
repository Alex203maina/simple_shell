#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
/* Structure for linked list */
typedef struct list_s {
    char *str;
    struct list_s *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguments to pass into a function,
 *                  allowing a uniform prototype for the function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct info_s {
    char **environ;
    list_t *aliases;
    list_t *history;
    char *line;
    char **args;
    char **argv;
    int interactive;
    int status;
    int hist_count;
    int is_pipe;
} info_t;


#define INFO_INIT                                                                        \
    { NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0 }

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;
/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _putnchar(char, int);
int _putnstr(char *, int, int);
int print_list(list_t *);
int _env(info_t *);
int _setenv(info_t *);
int _unsetenv(info_t *);
int setenv_linked(info_t *, char *, char *, int);
int _cd(info_t *);
int _alias(info_t *);
int _history(info_t *);
int _unalias(info_t *);
int _help(info_t *);
int _exit(info_t *);
int alias_linked(info_t *, char *, char *);
int print_hist(info_t *);
int remove_hist_node(list_t **, int);

/* toem_getline.c */
int get_line(info_t *);

/* toem_strtok.c */
int count_tokens(char *, char *);
int count_tokens1(char *, char *);
void free_tokens(char **);
char **tokarr(char *, char *);

/* toem_history.c */
int init_hist(info_t *);
int add_hist_node(list_t **, char *, int);
int write_hist(info_t *);
char *hist_pattern(info_t *, char *);

/* toem_history1.c */
list_t *new_hist_node(char *, int);
int hist_list_to_file(info_t *, char *);
void free_hist_list(list_t **);

/* toem_builtin1.c */
int _printenv(char **);
char *get_env_val(char *, char **);
int remove_env(list_t **, char *);
char **copy_environ(char **);
list_t *environ_to_list(char **);
int setenv_list(list_t **, char *, char *, int);

/* toem_itoa.c */
char *_itoa(int);

#endif /* SHELL_H */
