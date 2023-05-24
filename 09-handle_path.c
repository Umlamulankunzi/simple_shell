#include "00-main.h"

/**
 * is_executable - checks if @cmd_path is executable file
 * @cmd_path: path to file
 * Return: (1) if @cmd_path is executable Else (0)
 */
int is_executable(char *cmd_path)
{
	if (access(cmd_path, X_OK) == 0)
		return (1);
	return (0);
}

/**
 * concatenate_path_str - concatenate path strings to form valid path string
 * @str1: first string
 * @str2: second string
 * @sep: string seperator of @str1 and @str2
 * Return: string path to executable
 */
char *concatenate_path_str(char *str1, char *str2, char *sep)
{
	size_t len1 = _strlen(str1);
	size_t len2 = _strlen(str2);
	char *result = malloc(len1 + len2 + 2); /* allocate memory */

	if (result == NULL)
		return (NULL); /* error handling for failed memory allocation */

	_strcpy(result, str1); /* copy first string to the result string */
	_strcat(result, sep);  /* concatenate path seperator to result string */
	_strcat(result, str2); /* concatenate second string to the result string */
	return (result);
}

/**
 * get_cmd_path - Get the full executable path of @cmd
 * @env: pointer to head of environment linked list
 * @cmd: name of variable to get value of from environment
 *
 * Description: search the PATH environment variable to find the @cmd
 * executable. Return string path to executable command if found.
 * Note calling function is responsible for freeing the allocated memory.
 * If command not found function returns NULL.
 *
 * Return: char* path to command
 */
char *get_cmd_path(Node **env, char *cmd)
{
	char *path = _strdup_(_getenv_(env, "PATH"));
	char *path_ptr = path;

	char *path_dir;
	char *cmd_path = NULL;

	if (is_executable(cmd))
	{
		free(path_ptr);
		return (_strdup_(cmd));
	}

	path_dir = _strtok(path, ":");

	/* Loop through each dir in the PATH and check if the command exists */
	while (path_dir != NULL)
	{
		/* Construct the full path to the command executable */
		cmd_path = concatenate_path_str(path_dir, cmd, PATH_SEP);

		if (is_executable(cmd_path))
		{
			free(path_ptr);
			return (cmd_path);
		}

		path_dir = _strtok(NULL, ":");
		free(cmd_path);
	}
	free(path_ptr);
	return (NULL);
}
