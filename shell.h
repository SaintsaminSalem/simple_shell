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
ssize_t buffer_input(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buffer(info_t *info, char *buf, size_t *i);
int custom_getline(info_t *info, char **ptr, size_t *length);
void block_ctrl_c(__attribute__((unused))int sig_num);

/* getinfo.c */
void initializeInfo(info_t *info);
void populateInfo(info_t *info, char **av);
void freeInfo(info_t *info, int all);

/* environ.c */
int printEnvironment(info_t *info);
char *getEnvironment(info_t *info, const char *name);
int setEnvironment(info_t *info);
int unsetEnvironment(info_t *info);
int populateEnvironmentList(info_t *info);

/* getenv.c */
char **copyEnvironment(info_t *info);
int unsetEnvironmentVariable(info_t *info, char *var);
int setEnvironmentVariable(info_t *info, char *var, char *value);

/* history.c */
char *getHistoryFile(info_t *info);
int readHistoryFromFile(info_t *info);
int buildHistoryList(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);
int writeHistoryToFile(info_t *info);

/* lists.c */
list_t *addNode(list_t **head, const char *str, int num);
list_t *addNodeEnd(list_t **head, const char *str, int num);
size_t printListStr(const list_t *h);
int deleteNodeAtIndex(list_t **head, unsigned int index);
void freeList(list_t **headPtr);

/* lists1.c */
size_t getListLength(const list_t *h);
char **listToStrings(list_t *head);
size_t printListContents(const list_t *h);
list_t *findNodeWithPrefix(list_t *node, char *prefix, char c);
ssize_t getNodeIndex(list_t *head, list_t *node);

/* vars.c */
int isCommandChainDelimiter(info_t *info, char *buf, size_t *p);
void checkChainStatus(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replaceAliases(info_t *info);
int replaceVariables(info_t *info);
int replaceString(char **old, char *new);

#endif
