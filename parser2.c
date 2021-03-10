#include "../minishell.h"

void	select_cmd(char **inputs, t_data *data)
{
	if (!ft_strcmp(inputs[0], "echo"))
		b_echo(inputs);
	else if (!ft_strcmp(inputs[0], "pwd"))
		b_pwd(data);
	else if (!ft_strcmp(inputs[0], "cd"))
		b_cd(inputs, data);
	else if (!ft_strcmp(inputs[0], "env"))
		b_env(data->env);
	else if (!ft_strcmp(inputs[0], "exit"))
		b_exit(inputs, data);
	else if (!ft_strcmp(inputs[0], "export"))
		b_export(inputs, data);
	else if (!ft_strcmp(inputs[0], "unset"))
		b_unset(inputs, data);
	else
	{
		exec(inputs, data);
	}
}

void	free_inputs(char **inputs)
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

void	close_fds(t_data *data)
{
	if (data->fd_in != 0)
	{
		close(data->fd_in);
		data->fd_in = 0;
	}
	if (data->fd_out != 1)
	{
		close(data->fd_out);
		data->fd_out = 1;
	}
}