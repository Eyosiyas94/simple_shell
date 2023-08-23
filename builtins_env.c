#include "shell.h"

/**
 * builtin_env - displays env where the shell runs
 * @data: structure data type for the data
 * Return: 0 if sucess, or other number if its declared in the arguments
 */
int builtin_env(data_of_program *data)
{
	int i;
	char cp[50] = {'\0'};
	char *copy = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				copy = str_duplicate(env_get_key(cp, data));
				if (copy != NULL)
					env_set_key(cp, data->tokens[1] + i + 1, data);

				/* print the environ */
				print_environ(data);
				if (env_get_key(cp, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					env_set_key(cp, copy, data);
					free(copy);
				}
				return (0);
			}
			cp[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - ..
 * @data: structure data type for the date
 * Return: 0 if sucess, or other number if its declared in the arguments
 */
int builtin_set_env(data_of_program *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - ..
 * @data: structure data type for the program data
 * Return: ..
 */
int builtin_unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
