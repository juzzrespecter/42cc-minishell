#include "../minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		data->status = 130;
		if (data->input)
			ft_putstr_fd("\nminishell> ", 2);
		if (data->input)
			free(data->input);
		data->input = ft_strdup("\0");
	}
	else if (sig == SIGQUIT)
		write(2, "\b\b  \b\b", 6);
}

void	sig_init(void)
{
	if (signal(SIGINT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
	else if (signal(SIGQUIT, handle_sig) == SIG_ERR)
		exit(EXIT_FAILURE);
}

