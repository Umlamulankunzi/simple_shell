#include "00-main.h"


/**
 * add_node - Adds a new node to the end of the linked list
 * @head: A pointer to head of linked list
 * @key: The name of the environment variable to add
 * @value: The value of the environment variable to add
 *
 */
void add_node(Node **head, char *key, char *value)
{
	Node *curr_node, *new_node = malloc(sizeof(Node));

	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return;
	}

	curr_node = *head;
	while (curr_node->next != NULL)
		curr_node = curr_node->next;

	curr_node->next = new_node;
}

/**
 * copy_env - copy the environment variables to the linked list @env
 * @head: pointer to head of linked list
 * @environ: Environment variable array of strings
 */
void copy_env(Node **head, char **environ)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		char *env_var = strdup(environ[i]);
		char *key = strtok(env_var, "=");
		char *value = strtok(NULL, "=");

		add_node(head, key, value);
		free(env_var);
		i++;
	}
}

/**
 * update_node - update the value of a node with a given key @key
 * @head: pointer to head of linked list
 * @key: The name of the environment variable
 * @value: The new value to update the environ variable with key @key
 *
 */
void update_node(Node **head, char *key, char *value)
{
	Node *curr_node = *head;

	while (curr_node != NULL)
	{
		if (_strcmp(curr_node->key, key) == 0)
		{
			free(curr_node->value);
			curr_node->value = _strdup_(value);
			return;
		}
		curr_node = curr_node->next;
	}
}


/**
 * find_node - search for a node with a given key @key
 * @head: pointer to head of linked list
 * @key: name of environment variable to search for
 * Return: pointer to node with key == @key else NULL if not found
 */
Node *find_node(Node **head, char *key)
{
	Node *curr_node = *head;

	while (curr_node != NULL)
	{
		if (_strcmp(curr_node->key, key) == 0)
			return (curr_node);

		curr_node = curr_node->next;
	}
	return (NULL);
}

/**
 * delete_node - delete a node with a given key @key
 * @head: pointer to head of linked list
 * @key: name of environment variable to delete
 */
void delete_node(Node **head, char *key)
{
	Node *curr_node = *head;
	Node *prev_node = NULL;

	while (curr_node != NULL)
	{
		if (strcmp(curr_node->key, key) == 0)
		{
			if (prev_node == NULL)
			{
				/* Node to delete is the head of the list */
				*head = curr_node->next;
			}
			else
			{
				/* Node to delete is not the head of the list */
				prev_node->next = curr_node->next;
			}
			free(curr_node->key);
			free(curr_node->value);
			free(curr_node);
			return;
		}
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
}
