#include "00-main.h"


/**
 * sigintHandler - SIGINT signal handler
 * @sig_num: Unused parameter
 *
 */
void sigintHandler(int __attribute__((unused))sig_num)
{
	signal(SIGINT, sigintHandler);
	print(1, "\n");
	prompt();
}




/**
 * init_app_data - initialise data for application runtime
 * @argv:  NULL terminated array of strings
 *
 * Return: App_Data* to initialised runtime datatype
 */
App_Data *init_app_data(char **argv)
{
	App_Data *app_data = malloc(sizeof(App_Data));

	app_data->app_name = argv[0];

	app_data->input_buffer = malloc(INPUT_BUFFER_SIZE);
	app_data->in_bf_size = INPUT_BUFFER_SIZE;
	app_data->parsed_args = malloc(MAX_PARSED_ARGS_SIZE * sizeof(char *));

	app_data->env_head = malloc(sizeof(Node **));
	app_data->alias_head = malloc(sizeof(Node **));

	app_data->items_in_arr = 0;
	app_data->arr_size = MEM_ARR_BUFFER;
	app_data->mem_arr = malloc(MEM_ARR_BUFFER * sizeof(void *));

	app_data->error_code = EXIT_SUCCESS;
	app_data->line_count = 0;

	return (app_data);
}

/**
 * main - main entry point of the program
 * @argc: number of arguments passed to program
 * @argv: NULL terminated array of strings
 * Return: 0 if successful
 */
int main(int argc, char *argv[])
{

	App_Data *app_data = init_app_data(argv);

	*(app_data->env_head) = NULL;
	*(app_data->alias_head) = NULL;
	initialise_env(app_data);

	if (!(isatty(STDIN_FILENO)))
	{
		print(1, "hie\n");
		get_input(app_data);
		execute_command(app_data);
		free_all_data(app_data);
	}

	else if (argc == 2)
	{
		print(1, "file name: %s\n", argv[1]);
		free_all_data(app_data);
		/* taking a file as input, open it, read & execute commands and exit */
	}

	else
	{ /* running in interactive mode */
		signal(SIGINT, sigintHandler);
		while (1)
		{
			prompt();
			get_input(app_data);
			execute_command(app_data);
		}
	}

	return (0);
}
