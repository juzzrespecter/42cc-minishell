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
				data->status = 2;
				return (ft_putstr_fd("Error: Too Many Arguments\n", 2));
			}
			data->status = ft_atoi(inputs[1]);
			if (data->status > 255 || data->status < 0)
				data->status = 255;
		}
		else
		{
			data->status = 2;
			return (ft_putstr_fd("Error: Numeric Argument Required\n", 2));
		}
	}
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &data->origin);
	save_history(data);
	free_env(inputs);
	free_data(data, data->status);
}
