#include "00-main.h"


/**
 * initialise_env - initialises the environment linked list
 * @app_data: application data struct for app runtime
 */
void initialise_env(App_Data *app_data)
{
	/* Initialise environ data */
	copy_env(app_data->env_head, environ);
}



/**
* len_list - finds the length of a  linked list @head
* @head: linked list head
* Return: length of list
*/
size_t len_list(Node *head)
{
	if (head)
		return (1 + len_list(head->next));
	return (0);
}




/**
 * print_list - print linked list
 * @head: pointer to head of linked list
 * @flag: int flag to determin to print alias style or env style
 *
 */
void print_list(Node **head, int flag)
{
	Node *curr_node;

	if (len_list(*head) == 0)
		return;

	curr_node = *head;

	while (curr_node != NULL)
	{
		if (flag == ENV)
			print(STDOUT_FILENO, "%s=%s\n", curr_node->key, curr_node->value);
		else if (flag == ALIAS)
			print(STDOUT_FILENO, "%s='%s'\n", curr_node->key, curr_node->value);

		curr_node = curr_node->next;
	}
}
