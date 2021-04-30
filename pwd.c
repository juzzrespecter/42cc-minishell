#include "minishell.h"

void	b_pwd(t_data *data)
{
	ft_putstr(data->pwd);
	ft_putstr("\n");
	data->status = 0;
}
