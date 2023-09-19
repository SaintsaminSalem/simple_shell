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
 *		allowing uniform prototype for function pointer struct
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


/* shloop.c */
int main_loop(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

/* parser.c */
int is_command_executable(info_t *info, char *path);
char *find_command_path(info_t *info, char *pathstr, char *cmd);


/* loophsh.c */
int loophsh(char **);

/* errors.c */
void print_to_stderr(char *str);
int write_char_to_stderr(char c);
int write_char_to_fd(char c, int fd);
int print_to_fd(char *str, int fd);

/* string.c */
int string_length(char *str);
int string_compare(char *str1, char *str2);
char *string_starts_with(const char *haystack, const char *needle);
char *string_concatenate(char *destination, char *source);

/* string1.c */
char *string_copy(char *destination, const char *source);
char *string_duplicate(const char *str);
void print_string(char *str);
int write_char(char c);

/* exits.c */
char *copy_string(char *destination, char *source, int n);
char *concatenate_string(char *destination, char *source, int n);
char *find_character(char *str, char c);

/* tokenizer.c */
char **split_string(char *str, char *delimiters);
char **split_string2(char *str, char delimiter);

/* realloc.c */
char *_memory_set(char *ptr, char byte, unsigned int size);
void free_string_array(char **str_array);
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* memory.c */
int free_and_null_ptr(void **ptr);

/* atoi.c */
int is_shell_interactive(info_t *info);
int is_character_delimiter(char c, char *delimiters);
int is_alpha_character(int c);
int string_to_integer(char *s);

/* errors1.c */
int string_to_integer_err(char *s);
void print_shell_error(info_t *info, char *error_message);
int print_line_number(int line_number, int fd);
char *convert_to_string(long int num, int base, int flags);
void remove_first_comment(char *buf);

/* builtin.c */
int _theexit(info_t *);
int _thecd(info_t *);
int _thehelp(info_t *);

/* builtin1.c */
int history_command(info_t *info);
int unset_alias_command(info_t *info, char *alias);
int set_alias_command(info_t *info, char *alias);
int print_alias_command(char *alias);
int alias_command(info_t *info);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* getenv.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
