#include "minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	b_exit(char **inputs, t_data *data)
{
	if (inputs[1])
	{
		if (is_number(inputs[1]))
		{
			if (inputs[2])
			{
				g_status = 2;
				return (ft_putstr_fd("Error: Too Many Arguments\n", 2));
			}
			g_status = ft_atoi(inputs[1]);
			if (g_status > 255 || g_status < 0)
				g_status = 255;
		}
		else
		{
			g_status = 2;
			return (ft_putstr_fd("Error: Numeric Argument Required\n", 2));
		}
	}
	free_env(inputs);
	free(data->pwd);
	free_env(data->env);
	exit(g_status);
}
