#include "00-main.h"


/**
 * is_numeric_str - verify whether string contains numbers only
 * @str: string to check if is numeric
 * Return: int, (1) if @str is numeric Else (0)
 */
int is_numeric_str(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}


/**
 * eof_exit - frees all memory and exits application when EOF encountered
 * @app_data: struct containg data for application runtime
 *
 */
void eof_exit(App_Data *app_data)
{
	print(1, "\n");
	free_all_data(app_data);
	exit(EXIT_SUCCESS);
}

/**
 * shell_exit - frees all memory and exits application
 * @app_data: struct containg data for application runtime
 *
 */
void shell_exit(App_Data *app_data)
{
	int exit_code;

	if (app_data->parsed_args[1] == NULL)
	{
		free_all_data(app_data);
		exit(EXIT_SUCCESS);
	}
	else
	{
		exit_code = _atoi(app_data->parsed_args[1]);

		if (!(is_numeric_str(app_data->parsed_args[1])))
		{
			print(2, "%s: %d: exit: Illegal number: %s\n",
				app_data->app_name, app_data->line_count,
				app_data->parsed_args[1]);
			return;
		}

		if (exit_code < 0)
		{
			print(2, "%s: %d: exit: Illegal number: %d\n",
				app_data->app_name, app_data->line_count, exit_code);
			return;
		}

		else if (exit_code > 255)
		{
			exit_code = exit_code % 256;
			free_all_data(app_data);
			exit(exit_code);
		}
		else
		{
			free_all_data(app_data);
			exit(exit_code);
		}
	}
}
