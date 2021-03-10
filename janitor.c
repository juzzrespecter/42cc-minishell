#include "minishell.h"

int	janitor(char **argv, t_data *data, int exit_code)
{
	int	i;

	i = 0;
	free_env(data->env);
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	return (exit_code);
}
