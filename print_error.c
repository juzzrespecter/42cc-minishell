#include "minishell.h"

int	print_error(char *cmd, char *err, int fd_err)	/* nombre del shell: nombre del proceso: error	*/
{
	write(fd_err, "bash: ", 6);
	write(fd_err, cmd, ft_strlen(cmd));
	write(fd_err, ": ", 2);
	write(fd_err, err, ft_strlen(err));
	return (1);
}
