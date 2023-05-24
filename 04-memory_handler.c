/**
 * DOC: memory management script.
 *
 * This script manages heap allocated memory.
 * By adding any and all pointers of dynamically allocated
 * memory, to the memory management array mem_arr.
 * A single pointer can be freed using free_and_remove_ptr
 * whilst the whole memory dynamically allocated by the whole
 * application, which is tracked by the this script, can be freed
 * using the free_memory function, which frees all heap
 * allocated memory
 */

#include "00-main.h"



/**
 * add_ptr - adds a void* of dynamically allocated memory to memory array
 * @app_data: pointer to struct containing all app data
 * @ptr: void ptr to address of head allocated memory
 */
void add_ptr(App_Data *app_data, void *ptr)
{
	unsigned int old_size;

	app_data->items_in_arr++;
	if (app_data->items_in_arr == app_data->arr_size)
	{
		old_size = app_data->arr_size;
		app_data->arr_size += MEM_ARR_BUFFER;

		app_data->mem_arr = _realloc(app_data->mem_arr, old_size,
									   app_data->arr_size * sizeof(void *));
	}
	app_data->mem_arr[app_data->items_in_arr - 1] = ptr;
}


/**
 * free_and_remove_ptr - frees void * @ptr and removes it from array
 * @app_data: pointer to struct containing all app data
 * @ptr: void * to heap allocated memory
 *
 */
void free_and_remove_ptr(App_Data *app_data, void *ptr)
{
	int i;
	int ptr_idx = get_index(app_data->mem_arr, app_data->items_in_arr, ptr);

	if (ptr_idx < 0)
		return;

	free(app_data->mem_arr[ptr_idx]);
	for (i = ptr_idx; i < app_data->items_in_arr; i++)
	{
		app_data->mem_arr[i] = app_data->mem_arr[i + 1];
	}
	app_data->items_in_arr--;
}


/**
 * get_index - gets the index of void * @ptr in mem_arr
 * @mem_arr: array of void * allocaated from heap
 * @len_arr: length of @mem_arr
 * @ptr: void * to heap allocated memory
 *
 * Return: int index of void * @ptr Else (-1) if not found
 */
int get_index(void **mem_arr, unsigned int len_arr, void *ptr)
{
	unsigned int index;

	for (index = 0; index < len_arr; index++)
	{
		if (ptr == mem_arr[index])
			return (index);
	}
	return (-1);
}
