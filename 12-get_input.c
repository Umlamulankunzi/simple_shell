#include "00-main.h"


/**
 * get_input - get input from user
 * @app_data: struct containing application data
 *
 */
void get_input(App_Data *app_data)
{
	ssize_t read_status;

	read_status = _getline(&(app_data->input_buffer),
			&(app_data->in_bf_size), STDIN_FILENO);

	if (read_status == -1)
		eof_exit(app_data);

	parse_input(app_data);
}


/**
 * parse_input - parse input entered by user
 * @app_data: struct containing application data
 *
 */
void parse_input(App_Data *app_data)
{
	char *token;
	int i = 0;

	/* //TODO! you can handle seperators and pipes here */
	remove_comment(app_data->input_buffer);

	/* Loop through the command line and split it into arguments */
	token = _strtok(app_data->input_buffer, " ");

	while (token != NULL && i < MAX_PARSED_ARGS_SIZE)
	{
		app_data->parsed_args[i] = token;
		i++;
		token = _strtok(NULL, " ");
	}
	app_data->parsed_args[i] = NULL;
}

/**
 * execute_command - executes the command entered by user
 * @app_data: struct containing application data
 *
 * Return: 0 if successful Else 1 on error
 */
int execute_command(App_Data *app_data)
{

	app_data->line_count++;

	if (app_data->parsed_args[0] == NULL)
		return (0);

	if (is_builtin(app_data->parsed_args[0]))
	{
		execute_builtin(app_data);
		return (0);
	}
	else
		execute(app_data);
	return (1);
}

/**
 * execute - executes non builit command entered by user
 * @app_data: struct containing application data
 *
 * Return: 0 if successful Else 1 on error
 */
int execute(App_Data *app_data)
{
	pid_t pid;
	/* Look for the executable in the PATH environment variable */
	char *exec_path = get_cmd_path(app_data->env_head, app_data->parsed_args[0]);
	char **env = list_to_environ(app_data->env_head);

	if (exec_path == NULL)
	{
		print(STDERR_FILENO, "%s: %d: %s: not found\n", app_data->app_name,
			  app_data->line_count, app_data->parsed_args[0]);
		free(exec_path);
		return (1);
	}
	pid = fork();

	if (pid == 0)
	{
		execve(exec_path, app_data->parsed_args, env);
		perror("error");
		_exit(1);
	}
	else if (pid > 0)
	{ /* Parent process: wait for the child process to complete */
		int status;

		waitpid(pid, &status, 0);
		free_environ(env);
		free(exec_path);
		return (WEXITSTATUS(status));
	}
	else
	{						   /* Fork() failed: */
		perror("Fork Failed"); /* TODO: print an error msg and exit. */
		return (1);
	}
}
