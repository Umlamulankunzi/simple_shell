#include "00-main.h"

/**
 * alias - manages aliases, prints
 * @app_data: struct containing data for application runtime
 *
 */
void alias(App_Data *app_data)
{
	size_t i;

	if (app_data->parsed_args[1] == NULL)
	{
		print_list(app_data->alias_head, ALIAS);
		return;
	}

	for (i = 1; app_data->parsed_args[i]; i++)
	{
		if (_strchr(app_data->parsed_args[i], '=') == NULL)
			print_alias(app_data->alias_head, app_data->parsed_args[i]);

		else
			set_alias(app_data->alias_head, app_data->parsed_args[i]);
	}
}


/**
 * print_alias - prints a single alias if found in list
 * @head: pointer to head of linked list
 * @key: string name of alias
 *
 */
void print_alias(Node **head, char *key)
{
	Node *node;

	node = find_node(head, key);

	if (node == NULL)
		print(STDERR_FILENO, "alias: %s not found\n", key);
	else
		print(STDOUT_FILENO, "%s='%s'\n", node->key, node->value);
}


/**
 * set_alias - updates or adds alias to linked list
 * @head: pointer to head of linked list
 * @str_alias: string alias key and value
 *
 */
void set_alias(Node **head, char *str_alias)
{
	Node *node;

	char *key = _strtok(str_alias, "=");
	char *value = _strtok(NULL, "=");

	node = find_node(head, key);

	if (node == NULL)
		add_node(head, key, value);
	else
		update_node(head, key, value);
}
