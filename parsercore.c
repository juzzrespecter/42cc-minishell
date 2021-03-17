#include "minishell.h"

void		select_cmd(char **inputs, t_data *data)
{
	if (!data->redir)
	{
		data->redir = 1;
		return ;
	}
//	if (!ft_strcmp(inputs[0], "echo"))
//		b_echo(inputs);
	else if (!ft_strcmp(inputs[0], "pwd"))
		b_pwd(data);
//	else if (!ft_strcmp(inputs[0], "cd"))
//		b_cd(inputs, data);
	else if (!ft_strcmp(inputs[0], "env"))
		b_env(data->env);
	else if (!ft_strcmp(inputs[0], "exit"))
		b_exit(inputs, data);
//	else if (!ft_strcmp(inputs[0], "export"))
//		b_export(inputs, data);
//	else if (!ft_strcmp(inputs[0], "unset"))
//		b_unset(inputs, data);
//	else
//	{
//		exec(inputs, data);
//	}
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

void		close_fds(t_data *data)
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

void		exit_pipe(t_data *data)
{
	free_inputs(data->env);
	if (g_input)
		free(g_input);
	free(data->pwd);
	exit(EXIT_SUCCESS);
}

int			parsercore(char *clean_input, t_data *data, int piped)
{
	char	**inputs;
	int		oldfd[2];

//	if (parser_error(clean_input))
//	{
//		free(clean_input);
//		return (0);
//	}
	oldfd[0] = dup(1);
	oldfd[1] = dup(0);
	clean_input = input_cleaner(clean_input);
	parser_redir(&clean_input, data);
	clean_input = input_cleaner(clean_input);
	inputs = input_split(clean_input);
	free(clean_input);
	select_cmd(inputs, data);
	free_inputs(inputs);
	dup2(oldfd[0], 1);
	dup2(oldfd[1], 0);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	if (piped)
		exit_pipe(data);
	return (0);
}
