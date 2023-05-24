#include "00-main.h"


/**
 * is_builtin - checks if @cmd is builtin or not
 * @cmd: string command to check if builtin
 * Return: 1 if @cmd is builtin Else 0
 */
int is_builtin(char *cmd)
{
	int i;
	char *builtins[] = {
		"alias", "cd", "env",
		"exit", "setenv",
		"unsetenv", NULL };

	for (i = 0; builtins[i]; i++)
	{
		if (strcmp(builtins[i], cmd) == 0)
			return (1);
	}
	return (0);
}



/**
 * execute_builtin - executes builtin command
 * @app_data: struct containing data for application runtime
 *
 */
void execute_builtin(App_Data *app_data)
{
	if (_strcmp(app_data->parsed_args[0], "alias") == 0)
		alias(app_data);

	else if (_strcmp(app_data->parsed_args[0], "cd") == 0)
		cd_builtin(app_data);

	else if (_strcmp(app_data->parsed_args[0], "env") == 0)
		print_env(app_data);

	else if (_strcmp(app_data->parsed_args[0], "exit") == 0)
		shell_exit(app_data);

	else if (_strcmp(app_data->parsed_args[0], "setenv") == 0)
		_setenv(app_data);

	else if (_strcmp(app_data->parsed_args[0], "unsetenv") == 0)
		_unsetenv(app_data);
}

