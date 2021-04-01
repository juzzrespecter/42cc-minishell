#include "minishell.h"

void	b_echo(char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	g_status = 0;
	while (argv[i] && !ft_strcmp(argv[i], "-n") && i++)
		n_flag = 1;
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
}
