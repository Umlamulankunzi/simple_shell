#include "00-main.h"



/**
 * free_environ - free memory allocated to environ array of strings
 * @env: pointer to head of linked list
 *
 */
void free_environ(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}


/**
 * free_memory_arr - frees all memory pointers stored in memory array
 * @app_data: struct containing application data
 *
 */
void free_memory_arr(App_Data *app_data)
{
	int i;

	for (i = 0; app_data->items_in_arr; i++)
		free(app_data->mem_arr[i]);
	free(app_data->mem_arr);
}


/**
 * free_list - free memory used by the linked list @env
 * @head: A pointer to struct contaning pointer to head of linked list
 */
void free_list(Node **head)
{
	Node *current = *head;

	while (current != NULL)
	{
		Node *next = current->next;

		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	free(head);
}


/**
 * free_all_data - free all application memory in prep for exit
 * @app_data: struct containing application data
 */
void free_all_data(App_Data *app_data)
{
	free(app_data->input_buffer);
	free(app_data->parsed_args);
	free_list(app_data->env_head);
	free_list(app_data->alias_head);
	free_memory_arr(app_data);
	free(app_data);
}
