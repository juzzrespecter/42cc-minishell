#include "minishell.h"

int		echo(t_cmd *cmd)
{
	int		n_flag;
	int		i;
	int		fd_out;
	char	**argv;

	n_flag = 0;
	i = 0;
	fd_out = cmd->fd_out;
	argv = cmd->argv;
	if (argv[1] != NULL)
		if (ft_strncmp(argv[1], "-n", ft_strlen(argv[1])))
			n_flag = true;
	while (argv[i + 1] != NULL)
	{
		arg = argv[i + 1];
		write(fd_out, arg, ft_strlen(arg));
		if (argv[i + 2] != NULL)
			write(fd_out, ' ', 1);
		else
			if (n_flag == 0)
				write(fd_out, '\n', 1);
	}
	return (0);
}
