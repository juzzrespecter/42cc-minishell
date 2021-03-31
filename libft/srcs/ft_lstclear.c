/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:59:11 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:38:42 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_lstcleaner(t_list *lst, void (*del)(void *))
{
	if (lst->next)
		ft_lstcleaner(lst->next, del);
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*alst;

	alst = *lst;
	ft_lstcleaner(alst, del);
	*lst = NULL;
}
