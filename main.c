#include "minishell.h"

void	free_data(t_data *data, int exit_code)
{
	free_env(data->env);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->origin);
	exit(exit_code);
}

void	data_init(t_data *data, char **env)
{
	data->env = copy_env(env);
	if (!data->env)
		exit(EXIT_FAILURE);
	data->pwd = getcwd(NULL, 0);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
	data->input = NULL;
	data->history_head = NULL;
	data->history_index = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	g_status = 0;
	g_input = NULL;
	data_init(&data, envp);
	build_history(&data);
	set_history_mode(&data);
	while (1)
	{
		//free(g_input);
		data.input = ft_strdup("");
		sig_init();
		ft_putstr_fd("DANFERminishell> ", 2);
		history_mode(&data);
		g_input = ft_strdup(data.input);
		free(data.input);
		parser_start(g_input, &data);
	}
	return (0);
}
