#include "minishell.h"

t_hlist	*ft_lstnew_2(void *content)
{
	struct s_hlist	*new;

	new = (struct s_hlist *)malloc(sizeof(struct s_hlist));
	ft_memset(new, 0, sizeof(t_hlist));
	if (new)
		new->content = content;
	return (new);
}

void	add_history(t_hlist **hist_head, t_hlist **hist_index, char *command)
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
			*hist_index = *hist_head;
		}
	}
}

char	*browse_history_up(t_hlist **history_index)
{
	char	*tmp;

	if (*history_index)
	{
		tmp = (*history_index)->content;
		if ((*history_index)->next != NULL)
			(*history_index) = (*history_index)->next;
		return (tmp);
	}
	return (NULL);
}

char	*browse_history_down(t_hlist **history_index)
{
	char	*tmp;

	if (*history_index)
	{
		tmp = (*history_index)->content;
		(*history_index) = (*history_index)->previous;
		return (tmp);
	}
	return (NULL);
}

/*char	*browse_history_down(t_hlist **history_index)
{
	char	*tmp;

	if (*history_index)
	{
		tmp = (*history_index)->content;
		if ((*history_index)->previous != NULL)
		{
			(*history_index) = (*history_index)->previous;
		}
	}
}*/

int	putchar_2(int c)
{
	return (write(2, &c, 1));
}
