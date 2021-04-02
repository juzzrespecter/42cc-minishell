#include "minishell.h"

int	fd_in_redir(char *input, int i, t_data *data)
{
	int	fd;
	char pre_fd;

	pre_fd = 0;
	if (i == 0)
		return (-1);	
	fd = input[i - 1];
	if (i > 1)
		pre_fd = input[i - 2];
	if (!(ft_strchr("012", input[i - 2]) && ft_strchr(" \t;|", pre_fd)))
		return (-1);
	return (fd);
}
