#include "minishell.h"

void	history_up(t_data *data)
{
	char	*tmp;

	if (data->history_index == NULL)
		data->history_index = data->history_head;
	if (data->history_head && data->history_head->next == NULL)
	{
		free(data->input);
		data->input = ft_strdup(data->history_head->content);
		clear_line(data);
		ft_putstr_fd(data->input, 2);
	}
	else
	{
		tmp = browse_history_up(&(data->history_index));
		if (tmp)
		{
			free(data->input);
			data->input = ft_strdup(tmp);
			clear_line(data);
			ft_putstr_fd(data->input, 2);
		}
	}
}

void	history_down(t_data *data)
{
	char	*tmp;

	tmp = browse_history_down(&(data->history_index));
	free(data->input);
	if (tmp)
		data->input = ft_strdup(tmp);
	else
		data->input = ft_strdup("");
	clear_line(data);
	if (tmp)
		ft_putstr_fd(data->input, 2);
}
