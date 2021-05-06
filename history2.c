#include "minishell.h"

int	clear_line(t_data *data)
{
	tputs(data->termc->clear_line, 1, putchar_2);
	tputs(data->termc->cariage_return, 1, putchar_2);
	ft_putstr_fd(data->prompt, STDOUT_FILENO);
	return (1);
}

void	get_history_from_file(int fd, t_data *data)
{
	char	*line;
	int		ret;

	line = NULL;
	ret = get_next_line(fd, &line);
	while (ret >= 0)
	{
		if (*line != '\0')
			add_history(&data->history_head, line);
		free(line);
		if (ret == 0)
			break ;
		ret = get_next_line(fd, &line);
	}
}

void	build_history(t_data *data)
{
	int		fd;

	fd = open(HIST_FILE, O_RDONLY);
	if (fd >= 0)
	{
		get_history_from_file(fd, data);
		close(fd);
	}
}

void	history_tail(t_data *data)
{
	int		i;

	i = 0;
	data->history_index = data->history_head;
	while (i < HIST_SIZE && data->history_index)
	{
		if (!data->history_index->next)
			break ;
		data->history_index = data->history_index->next;
		i++;
	}
}

void	save_history(t_data *data)
{
	int		fd;
	char	*tmp;

	fd = open(HIST_FILE, O_APPEND | O_CREAT | O_RDWR, 0666);
	if (fd >= 0)
	{
		history_tail(data);
		while (data->history_index)
		{
			tmp = ft_strjoin(data->history_index->content, "\n");
			ft_putstr_fd(tmp, fd);
			free(tmp);
			data->history_index = data->history_index->previous;
		}
		close(fd);
	}
}
