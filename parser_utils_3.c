#include "minishell.h"

int		is_fd(char *input)
{
	int	i;

	i = 0;
	while (input[i] && !ft_strrchr(";|\t <>", input[i]))
	{
		if (!ft_isdigit(input[i]))
			return (0);
		i++;
	}
	return (i);
}
