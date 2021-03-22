#include "minishell.h"
#include <stdio.h>

int	janitor(t_data *data, int exit_code)
{
	int	i;

	i = 0;
	free_env(data->env);
	/*while (env->argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);*/
	return (exit_code);
}

void		free_inputs(char **inputs)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		free(inputs[i]);
		i++;
	}
	free(inputs);
}
