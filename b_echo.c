#include "minishell.h"

int	b_echo_set_flag(char *flag_cmd)
{
	int	cmp_out;

	if (flag_cmd == NULL)
		return (0);
	cmp_out = ft_strncmp(flag_cmd, "-n", ft_strlen(flag_cmd));
	if (cmp_out == 0)
		return (1);
	return (0);
}

int	b_echo(char **argv)
{
	int		n_flag;
	int		i;

	n_flag = b_echo_set_flag(argv[1]);
	i = 0;
	if (n_flag)
		i++;
	while (argv[i + 1] != NULL)
	{
		write(1, argv[i + 1], ft_strlen(argv[i + 1]));
		if (argv[i + 2] != NULL)
			write(1, " ", 1);
		else
			if (n_flag == 0)
				write(1, "\n", 1);
		i++;
	}
	g_status = 0;
	return (0);
}
