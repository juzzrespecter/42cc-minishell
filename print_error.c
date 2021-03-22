#include "minishell.h"

int	print_error(char *cmd, char *err)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	return (1);
}
