/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lstmap_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:15:06 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:43:05 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*alst;
	t_list	*nlst;

	if (!lst)
		return (NULL);
	alst = NULL;
	while (lst)
	{
		nlst = ft_lstnew(ft_strdup(lst->content));
		if (!nlst)
			return (NULL);
		nlst->content = f(nlst->content);
		if (!nlst)
			del(nlst->content);
		ft_lstadd_back(&alst, nlst);
		lst = lst->next;
	}
	return (alst);
}
