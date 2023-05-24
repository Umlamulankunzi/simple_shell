#include "00-main.h"


/**
 * cd_setenv - initialise a new environment variable or update existing one
 * @app_data: Struct containing Data for Application runtime
 * @name: name of environment variable to update or initialise
 * @new_value: value of environment variable
 * @flag: flag: 1 to overwrite, 0 to not overwrite if variable exists
 *
 * Return: 0 on success Else -1 on failure
 */
int cd_setenv(App_Data *app_data, char *name, char *new_value, int flag)
{
	Node *node;

	if (name == NULL || new_value == NULL)
	{
		print(STDERR_FILENO, "%s: %d: setenv: Invalid key or value\n",
			app_data->app_name, app_data->line_count);
		return (-1);
	}

	node = find_node(app_data->env_head, name);

	if (node == NULL)
	{
		add_node(app_data->env_head, name, new_value);
		return (0);
	}

	else
	{
		if (flag)
			update_node(app_data->env_head, name, new_value);


		return (0);
	}
}


/**
 * cd_builtin - change working directorate of app and update environment
 * @app_data: struct containing data for application runtime
 *
 */
void cd_builtin(App_Data *app_data)
{
	char *cwd, *oldpwd, *new_pdw, *buffer;
	size_t buffer_size = MAX_CD_PATH_LEN;
	int status;

	cwd = app_data->parsed_args[1];

	if (cwd == NULL || (_strcmp(cwd, "~") == 0))
		cwd = _getenv_(app_data->env_head, "HOME");

	if (_strcmp(cwd, "-") == 0)
		cwd = _getenv_(app_data->env_head, "OLDPWD");

	oldpwd = _getenv_(app_data->env_head, "PWD");

	if (oldpwd == NULL)
		oldpwd = "";

	if (chdir(cwd) != 0)
		perror("cd");

	status  = cd_setenv(app_data, "OLDPWD", oldpwd, 1);

	if (status != 0)
		perror("setenv");

	buffer = malloc(buffer_size * sizeof(char));
	new_pdw = getcwd(buffer, buffer_size);

	status  = cd_setenv(app_data, "PWD", new_pdw, 1);

	if (status != 0)
		perror("setenv");

	free(buffer);

}
