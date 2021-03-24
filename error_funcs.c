#include "minishell.h"
#include <stdio.h>

int		janitor(char **argv, t_data *data, int exit_code)
{
	int	i;

	i = 0;
	if (exit_code == 127)
		print_error(argv[0], "command not found\n", exit_code);
	if (argv != NULL)
		free_inputs(argv);
	free_env(data->env);
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

int	print_error(char *msg1, char *msg2, int exit_code)
{
	write(2, "bash: ", 6);
	if (exit_code == 258)
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, msg1, ft_strlen(msg1));
		write(2, "'\n", 2);
	}
	else
	{
		write(2, msg1, ft_strlen(msg1));
		write(2, ": ", 2);
		write(2, msg2, ft_strlen(msg2));
		write(2, "\n", 1);
	}
	g_status = exit_code;
	return (exit_code);
}
