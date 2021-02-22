/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:10:36 by danrodri          #+#    #+#             */
/*   Updated: 2019/11/14 18:59:11 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*memdst;
	unsigned const char	*memsrc;

	memsrc = src;
	memdst = dst;
	i = 0;
	while (i < n)
	{
		memdst[i] = memsrc[i];
		i++;
	}
	return (memdst);
}
