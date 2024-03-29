#include "minishell.h"

extern t_data g_data;

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_data.status = 130;
		if (g_data.input)
		{
			ft_putchar_fd('\n', 2);
			ft_putstr_fd(g_data.prompt, 2);
		}
		if (g_data.input)
			free(g_data.input);
		g_data.input = ft_strdup("\0");
		g_data.history_index = NULL;
	}
}

void	sig_init(void)
{
	if (signal(SIGINT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}

void	handle_exec_sig(int sig)
{
	if (sig == SIGINT)
	{
		if (g_data.input)
			free(g_data.input);
		g_data.status_signal = 130;
		write(2, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_data.status_signal = 131;
		ft_putstr_fd("Exit (core dumped)\n", 2);
	}
}

void	sig_exec_init(void)
{
	if (signal(SIGINT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, handle_exec_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}
