#include "minishell.h"

int		set_sig(t_data *data)
{
	int		brk;

	brk = 0;
	if (g_status == -2)  
		g_status = 0;
	if (g_status == -1) 
	{
		g_status = 0;
		free(data->input);
		data->input = ft_strdup("");
		brk = 1;
	}
	return (brk);
}

void	history_up(t_data *data)
{
	char *tmp;

	if (data->history_index == NULL)
		data->history_index =  data->history_head;
	if (data->history_head && data->history_head->next == NULL)
	{
		free(data->input);
		data->input = ft_strdup(data->history_head->content);
		clear_line(data);
		ft_putstr_fd(data->input, 2);
	}
	else if ((tmp = browse_history_up(&(data->history_index))))
	{
		free(data->input);
		data->input = ft_strdup(tmp);
		clear_line(data);
		ft_putstr_fd(data->input, 2);
	}
}

void	history_down(t_data *data)
{
	char	*tmp;

	tmp = browse_history_down(&(data->history_index));
	free(data->input);
	data->input = (tmp)? ft_strdup(tmp): ft_strdup("");
	clear_line(data);
	if (tmp)
		ft_putstr_fd(data->input, 2);
}

void	delete_char(t_data *data)
{
	if (data->input[0] != '\0')
		data->input[ft_strlen(data->input) - 1] = '\0';
	clear_line(data);
	ft_putstr_fd(data->input, STDOUT_FILENO);
}

void	end_of_file(t_data *data)
{

	if (data->input[0] == '\0')
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		tcsetattr(0, TCSANOW, &data->origin);
		save_history(data);
		exit(0);
	}
}

void	append_to_holder(char *buffer, t_data *data)
{
	char *tmp;

	tmp = data->input;
	data->input = ft_strjoin(data->input, buffer);
	free(tmp);
	//clear_line(data);
	ft_putchar_fd(data->input[ft_strlen(data->input) - 1], STDOUT_FILENO);
}

void	return_input(t_data *data)
{
	write(2, "\n", 1);
	add_history(&(data->history_head), &(data->history_index), data->input);
}
