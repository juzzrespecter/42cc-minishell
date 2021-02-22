/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:16:13 by danrodri          #+#    #+#             */
/*   Updated: 2019/11/12 16:23:14 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*memdst;
	const unsigned char	*memsrc;
	size_t				i;

	memdst = dst;
	memsrc = src;
	i = 0;
	if (memdst > memsrc)
	{
		while (i < len)
		{
			memdst[len - i - 1] = memsrc[len - i - 1];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			memdst[i] = memsrc[i];
			i++;
		}
	}
	return (memdst);
}
