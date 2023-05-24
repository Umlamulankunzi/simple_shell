#include "00-main.h"


/**
 * print_env - prints the environment variable
 * @app_data: struct containing Data for the application runtime
 *
 */
void print_env(App_Data *app_data)
{
	print_list(app_data->env_head, ENV);
}


/**
 * _setenv - initialise a new environment variable or update existing one
 * @app_data: Struct containing Data for Application runtime
 *
 */
void _setenv(App_Data *app_data)
{
	Node *node;

	if (app_data->parsed_args[1] == NULL || app_data->parsed_args[2] == NULL)
	{
		print(STDERR_FILENO, "%s: %d: setenv: Invalid key or value",
			app_data->app_name, app_data->line_count);
		return;
	}

	node = find_node(app_data->env_head, app_data->parsed_args[1]);

	if (node == NULL)
		add_node(app_data->env_head, app_data->parsed_args[1],
			app_data->parsed_args[2]);

	else
		update_node(app_data->env_head, app_data->parsed_args[1],
			app_data->parsed_args[2]);
}


/**
 * _unsetenv - remove an environment variable
 * @app_data: Struct containing Data for Application runtime
 *
 *
 */
void _unsetenv(App_Data *app_data)
{
	Node *node;

	if (app_data->parsed_args[1] == NULL)
	{
		print(STDERR_FILENO, "%s: %d: unsetenv: Invalid name",
			app_data->app_name, app_data->line_count);
	}

	node = find_node(app_data->env_head, app_data->parsed_args[1]);

	if (node == NULL)
		print(STDERR_FILENO, "%s: %d: unsetenv: not found",
			app_data->app_name, app_data->line_count);

	else
		delete_node(app_data->env_head, app_data->parsed_args[1]);
}


/**
 * _getenv_ - custom getenv function that gets value of environment variable
 * @env: pointer to head of environment linked list
 * @name: string name of environment variable to get
 * Return: char *pointer to value of variable @name, Else (NULL)
 */
char *_getenv_(Node **env, char *name)
{
	Node *node;

	node = find_node(env, name);
	if (node == NULL)
		return (NULL);

	return (node->value);
}


/**
 * list_to_environ - generate an envrion variable to pass to child processes
 * @head: pointer to head of environment linked list
 *
 * Return: NULL terminated array of strings
 */
char **list_to_environ(Node **head)
{
	size_t i = 0, count = len_list(*head);
	char **new_environ = malloc((count + 1) * sizeof(char *));

	Node *curr = *head;

	if (new_environ == NULL)
		return (NULL);


	while (curr != NULL)
	{
		char *str = concatenate_path_str(curr->key, curr->value, "=");

		if (str == NULL)
			return (NULL);

		new_environ[i] = str;
		curr = curr->next;
		i++;
	}

	new_environ[count] = NULL;

	return (new_environ);

}
