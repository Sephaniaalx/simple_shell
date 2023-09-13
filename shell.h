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

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - struct for singly linked list
 * @num: the num field
 * @str: string
 * @next: this points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
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
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - struct contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* shell_loop.c */
int shell_loop(info_t *, char **);
int f_builtin(info_t *);
void f_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int is_cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *f_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void f_free(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int b_free(void **);

/*atoi.c */
int interactive(info_t *);
int is_delimeter(char, char *);
int is_alpha(int);
int atoi_(char *);

/* errors_1.c */
int err_atoi(char *);
void p_error(info_t *, char *);
int print_decimal(int, int);
char *c_number(long int, int, int);
void r_comments(char *);

/* builtin.c */
int exit_(info_t *);
int _cd(info_t *);
int help(info_t *);

/* builtin_1.c */
int _history(info_t *);
int _alias(info_t *);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void siginthandler(int);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void f_info(info_t *, int);

/* environ.c */
char *get_env(info_t *, const char *);
int _env(info_t *);
int set_env(info_t *);
int _unsetenv(info_t *);
int p_env_list(info_t *);

/* get_env.c */
char **get_environ(info_t *);
int un_setenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *get_hist_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int build_hist_list(info_t *info, char *buf, int linecount);
int re_number_hist(info_t *info);

/* lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_to_end(list_t **, const char *, int);
size_t p_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void f_list(list_t **);

/* list_1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t p_list(const list_t *);
list_t *node_start_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int r_alias(info_t *);
int r_vars(info_t *);
int r_string(char **, char *);

#endif


