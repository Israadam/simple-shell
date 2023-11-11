#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* sh_loop.c */
int shll(info_t *, char **);
int check_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* my_path.c */
int _cmd(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *path_str(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* erc_string_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfw(char c, int fd);
int _printsfd(char *str, int fd);

/* str1.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *start_with(const char *, const char *);
char *_strcat(char *, char *);

/* str2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* str3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* str4.c */
char **strspt(char *, char *);
char **strspt2(char *, char);

/* my_memory.c */
char *my_memset(char *, char, unsigned int);
void str_free(char **);
void *realloc_mem(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int bfree(void **);

/* more_functions.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* more_functions2.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin_emu.c */
int _exitsh(info_t *);
int _dirp(info_t *);
int _mycd(info_t *);

/* builtin_emu2.c */
int _histlst(info_t *);
int unset_alias(info_t *, char *);
int set_alias(info_t *, char *);
int print_alias(list_t *);
int _myalias(info_t *);




/* getline.c module */
ssize_t input_buffer(info_t *);
int _getnxtline(info_t *, char **, size_t *);
void sigintcntrl(int);
ssize_t set_input(info_t *);



/* info.c module */
void int_info(info_t *);
void str_info(info_t *, char **);
void free_infor(info_t *, int);

/* env.c module */
char *_getenv(info_t *, const char *);
int _prenv(info_t *);
int _newsetenv(info_t *);
int _unsetenv(info_t *);
int populate_env_list(info_t *);

/* env2.c module */
char **set_environ(info_t *);
int _rmenv(info_t *, char *);
int _nwsenv(info_t *, char *, char *);

/* file_io_functions.c */
char get_thehistory_file(info_t *info);
int wrt_history(info_t *info);
int read_history(info_t *info);
int build_history_link(info_t *info, char *buf, int linecount);
int renumber_hist(info_t *info);

/* liststr.c module */
list_t *add_node_list(list_t **, const char *, int);
list_t *add_end_node(list_t **, const char *, int);
size_t print_lst_str(const list_t *);
int delete_node_at_given_index(list_t **, unsigned int);
void free_node_list(list_t **);

/* list2.c */
size_t list_length(const list_t *);
char **list_strings(list_t *);
size_t printlist(const list_t *);
list_t *starts_with(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
