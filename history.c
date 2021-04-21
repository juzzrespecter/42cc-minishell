#include "minishell.h"

h_list	*ft_lstnew_2(void *content)
{
	struct z_list *new;

	new = (struct z_list *)malloc(sizeof(struct z_list));
	ft_memset(new, 0, sizeof(h_list));
	if (new)
		new->content = content;
	return (new);
}

void	add_history(h_list **hist_head, h_list **hist_index, char *command)
{
	h_list		*new = NULL;

	if (*command)
	{
		if (((*hist_head) && ft_strcmp((*hist_head)->content, command)) ||
			!(*hist_head))
			new = ft_lstnew_2(ft_strdup(command));
		if (new)
		{
			if (!(*hist_head))
				*hist_head = new;
			else
			{
				new->next = *hist_head;
				(*hist_head)->previous = new;
				*hist_head = new;
			}
			*hist_index = *hist_head;
		}
	}
}

char	*browse_history_up(h_list **history_index)
{
	char *tmp;

	if (*history_index)
	{
		tmp = (*history_index)->content;
		if ((*history_index)->next != NULL)
			(*history_index) = (*history_index)->next;
		return (tmp);
	}
	return (NULL);
}

char	*browse_history_down(h_list **history_index)
{
	char	*tmp;

	if ((*history_index))
	{
		tmp = (*history_index)->content;
		(*history_index) = (*history_index)->previous;
		return (tmp);
	}
	return (NULL);
}

int		putchar_2(int c)
{
	return (write(2, &c, 1));
}

int		clear_line(t_data *data)
{
	tputs(data->termc->clear_line, 1, putchar_2);
	tputs(data->termc->cariage_return, 1, putchar_2);
	ft_putstr_fd("DANFERminishell", 2);
	return (1);
}

void	get_history_from_file(int fd, t_data *data)
{
	int		ret;
	char	*line;
	int		hist_count;
	h_list 	*hist_tail;

	hist_count = 0;
	line = NULL;
	hist_tail = NULL;
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		if (*line != '\0')
		{
			hist_count++;
			add_history(&data->history_head, &data->history_index, line);
			if (hist_count == 1)
				hist_tail = data->history_head;
			if (hist_count > HIST_SIZE)
			{
				hist_tail = hist_tail->previous;
				free(hist_tail->next->content);
				free(hist_tail->next);
				hist_tail->next = NULL;
			}
		}
		free(line);
		line = NULL;
		if (ret == 0)
			break;
	}

}

void	build_history(t_data *data)
{
	int		fd;

	if ((fd = open(HIST_FILE, O_RDONLY)) >= 0)
	{
		get_history_from_file(fd, data);
		close(fd);
	}
}

void		history_tail(t_data *data)
{
	int		i;

	i = 0;
	data->history_index = data->history_head;
	while (i < HIST_SIZE && data->history_index)
	{
		if (!data->history_index->next)
			break;
		data->history_index = data->history_index->next;
		i++;
	}
}



void	save_history(t_data *data)
{
	int		fd;
	char	*tmp;

	fd = open(HIST_FILE, O_CREAT | O_TRUNC, 0666);
	close(fd);
	fd = open(HIST_FILE, O_APPEND | O_CREAT | O_RDWR, 0666);
	printf("%d\n", fd);
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
