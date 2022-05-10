#include "minishell.h"

int	set_sig(t_data *data)
{
	int	brk;

	brk = 0;
	if (data->status == -2)
		data->status = 0;
	if (data->status == -1)
	{
		data->status = 0;
		free(data->input);
		data->input = ft_strdup("");
		brk = 1;
	}
	return (brk);
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
		tcsetattr(0, TCSAFLUSH, &data->origin);
		save_history(data);
		exit(0);
	}
}

void	append_to_holder(char *buffer, t_data *data)
{
	char	*tmp;

	tmp = data->input;
	data->input = ft_strjoin(data->input, buffer);
	free(tmp);
	ft_putchar_fd(data->input[ft_strlen(data->input) - 1], STDOUT_FILENO);
}

void	return_input(t_data *data)
{
	write(2, "\n", 1);
	add_history(&(data->history_head), data->input);
	data->history_index = NULL;
}
