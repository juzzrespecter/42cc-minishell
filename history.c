#include "minishell.h"

t_hlist	*ft_lstnew_2(void *content)
{
	struct s_hlist	*new;

	new = (struct s_hlist *)malloc(sizeof(struct s_hlist));
	ft_memset(new, 0, sizeof(t_hlist));
	if (new)
		new->content = content;
	new->previous = NULL;
	return (new);
}

void	add_history(t_hlist **hist_head, char *command)
{
	t_hlist	*new;

	new = NULL;
	if (*command)
	{
		if (((*hist_head) && ft_strcmp((*hist_head)->content, command)) \
				|| !(*hist_head))
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
		}
	}
}

char	*browse_history_up(t_hlist **history_index, t_hlist **history_head)
{
	char	*tmp;

	if (*history_index)
	{
		if ((*history_index)->next != NULL)
			(*history_index) = (*history_index)->next;
		tmp = (*history_index)->content;
		return (tmp);
	}
	*history_index = *history_head;
	return ((*history_index)->content);
}

char	*browse_history_down(t_hlist **history_index)
{
	char	*tmp;

	tmp = NULL;
	if (*history_index)
	{
		(*history_index) = (*history_index)->previous;
		if (*history_index)
			tmp = (*history_index)->content;
	}
	return (tmp);
}

int	putchar_2(int c)
{
	return (write(2, &c, 1));
}
