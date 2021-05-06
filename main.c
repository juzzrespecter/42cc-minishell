#include "minishell.h"

void	free_data(t_data *data, int exit_code)
{
	free_env(data->env);
	free(data->pwd);
	ft_putstr_fd("exit\n", 2);
	exit(exit_code);
}

void	data_init(t_data *data, char **env)
{
	data->status = 0;
	data->status_signal = 0;
	data->input = NULL;
	data->env = copy_env(env);
	if (!data->env)
		exit(EXIT_FAILURE);
	data->pwd = getcwd(NULL, 0);
	data->fd_in = 0;
	data->fd_out = 1;
	data->redir = 1;
	data->history_head = NULL;
	data->history_index = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	data_init(&g_data, envp);
	build_history(&g_data);
	set_history_mode(&g_data);
	sig_init();
	while (1)
	{
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_data.modified);
		ft_putstr_fd("DANFERminishell> ", 2);
		g_data.input = ft_strdup("");
		history_mode(&g_data);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_data.origin);
		parser_start(g_data.input, &g_data);
	}
	return (0);
}
