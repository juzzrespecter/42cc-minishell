#include "minishell.h"

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

void	exit_pipe(t_data *data)
{
	free_inputs(data->env);
	free(data->pwd);
	exit(data->status);
}

int	parsercore(char *clean_input, t_data *data, int piped)
{
	char	**inputs;
	int		oldfd[2];

	oldfd[0] = dup(1);
	oldfd[1] = dup(0);
	clean_input = input_cleaner(clean_input);
	parser_redir(&clean_input, data);
	clean_input = expand_variables(clean_input, data);
	clean_input = input_cleaner(clean_input);
	if (*clean_input != 0)
	{
		inputs = input_split(clean_input);
		free(clean_input);
		select_cmd(inputs, data);
		free_inputs(inputs);
	}
	dup2(oldfd[0], 1);
	dup2(oldfd[1], 0);
	close_fds(data);
	close(oldfd[0]);
	close(oldfd[1]);
	if (piped)
		exit_pipe(data);
	return (0);
}
