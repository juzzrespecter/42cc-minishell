#include "minishell.h"

void	free_data(t_data *data, char *user_input)
{
	free_env(data->env);
	free(user_input);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

void	data_init(t_data *data, char **env)
{
	data->env = copy_env(env);
	data->pwd = getcwd(NULL, 0);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
}

int		main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		ret;

	argc = 0;
	argv = NULL;
	data_init(&data, envp);
	g_status = 0;
	g_input = NULL;
	if (!data.env)
		exit(EXIT_FAILURE);
	while (1)
	{
		free(g_input);
		sig_init();
		ft_putstr_fd("DANFERminishell> ", 2);
		ret = get_next_line(0, &g_input);
		if (!ret)
			free_data(&data, g_input);
		else
			parser_start(g_input, &data);
	}
	return (0);
}
