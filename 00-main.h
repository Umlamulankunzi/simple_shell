#ifndef MAIN_H
#define MAIN_H

/* INCLUDES */
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define INPUT_BUFFER_SIZE 2048
#define MEM_ARR_BUFFER 500
#define MAX_PATH_LEN 2048
#define MAX_CD_PATH_LEN 1024
#define COMMENT_CHAR '#'
#define MAX_PARSED_ARGS_SIZE 1024

#define ENOENT_MSG "No such file or directory"
#define EACCES_MSG "Permission denied"
#define CMD_NOT_FOUND "not found"
#define EEXIT_MSG "Illegal number"

#define ENOENT_CODE ENOENT
#define EACCES_CODE EACCES
#define ECNEXIST_CODE 44
#define EEXIT_CODE 45

#define ENV		1
#define ALIAS	2

#define PATH_SEP "/"

extern char **environ;

/**
 * struct Node - Node in linked list
 * @key: The name variable
 * @value: The value of the variable
 * @next: A pointer to the next node in the linked list
 */
typedef struct Node
{
	char *key;
	char *value;
	struct Node *next;
} Node;

/* creating a struct with all the app data required to run the app */
/**
 * struct data - struct containing all app data required for app runtime
 * @app_name: name of application
 * @input_buffer: buffer to store user input
 * @in_bf_size: input buffer size in bytes
 * @parsed_args: NULL terminated array of tokenized strings from input_buffer
 * @env_head: pointer to head of environment linked list
 * @alias_head: pointer to head of alias linked list
 * @mem_arr: array of void * to malloc'd memory
 * @items_in_arr: total void * in @mem_arr
 * @arr_size: size of @mem_arr
 * @error_code: error code
 * @line_count: line count of command entered
 *
 */
typedef struct data
{
	char *app_name;

	/* INPUT VARIABLES */
	char *input_buffer;
	size_t in_bf_size;

	/* PARSED BUFFER */
	char **parsed_args;

	/* ENVIRONMENT VARIABLES */
	Node **env_head;

	/* ALIAS VARIABLES */
	Node **alias_head;

	/* MEMORY MANAGEMENT VARIABLES */
	void **mem_arr;	  /* memory array to store void pointers */
	int items_in_arr; /* record of total items currently stored */
	int arr_size;	  /* total size of mem_arr */

	/* ERROR VARIABLES */
	int error_code;
	int line_count;

} App_Data;

/* FUNCTION PROTOTYPES IMPLEMENTED */

void sigintHandler(int sig_num);

/****** 02-INIT-APP-DATA ***********/

/****** 03-HELPER1 *****************/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strtok(char *str, const char *delim);
ssize_t _getline(char **lineptr, size_t *n, int fd);
char *_strdup_(const char *str);
int _strlen(const char *str);

/****** 03-HELPER2 *****************/
char *_strcat(char *dest, const char *src);
int _strcmp(char *str1, char *str2);
char *_strcpy(char *dest, const char *src);
char *_strchr(const char *str, int ch);
int _atoi(const char *str);

/****** 04-MEMORY-HANDLER **********/
void init_mem_arr(App_Data *app_data);
void add_ptr(App_Data *app_data, void *ptr);
void free_and_remove_ptr(App_Data *app_data, void *ptr);
int get_index(void **mem_arr, unsigned int len_arr, void *ptr);

/****** 05-FREE-MEMORY *************/
void free_environ(char **env);
void free_memory_arr(App_Data *app_data);
void free_list(Node **head);
void free_all_data(App_Data *app_data);


/****** 06-PROMPT ******************/
void prompt(void);


/****** 07-ENV-AND-ALIAS1 ***************/
void add_node(Node **head, char *key, char *value);
void copy_env(Node **head, char **environ);
void update_node(Node **head, char *key, char *value);
Node *find_node(Node **head, char *key);
void delete_node(Node **head, char *key);


/****** 07-ENV-AND-ALIAS2 ***************/
void initialise_env(App_Data *app_data);
void print_list(Node **head, int flag);
size_t len_list(Node *head);

/****** 07-ALIAS ******************/
void alias(App_Data *app_data);
void print_alias(Node **head, char *key);
void set_alias(Node **head, char *str_alias);

/****** 07-ENV ******************/
void print_env(App_Data *app_data);
void _setenv(App_Data *app_data);
void _unsetenv(App_Data *app_data);
char *_getenv_(Node **env, char *name);
char **list_to_environ(Node **head);

/****** 08-BUILTIN ****************/
int is_builtin(char *cmd);
void manage_builtin(App_Data);
void execute_builtin(App_Data *app_data);

/****** 09-HANDLE_PATH ************/
int is_executable(char *cmd_path);
char *concatenate_path_str(char *str1, char *str2, char *sep);
char *get_cmd_path(Node **env, char *cmd);

/****** 10-print *****************/
int _putchar(int fd, char c);
int _puts(int fd, char *s);
int _putnbr(int fd, int n);
int print(int fd, const char *format, ...);

/****** 11-comments **************/
void remove_comment(char *buffer);

/****** 12-GET_INPUT *************/
void get_input(App_Data *app_data);
void parse_input(App_Data *app_data);
int execute_command(App_Data *app_data);
int execute(App_Data *app_data);

/****** 13-EXIT ******************/
int is_numeric_str(char *str);
void shell_exit(App_Data *app_data);
void eof_exit(App_Data *app);

/****** 14-CHANGE_DIR ************/
int cd_setenv(App_Data *app_data, char *name, char *new_value, int flag);
void cd_builtin(App_Data *app_data);


/*
* //TODO! following functions to be implemented
* TO IMPLEMENT
* void execute_non_interactive(char *program_name, char *filename);
* void initialise_app_data(App_Data *app_data, char **argv, int *app_status);
* void execute_command(App_Data *app_data);
*/


#endif
