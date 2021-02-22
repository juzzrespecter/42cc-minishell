/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:45:36 by danrodri          #+#    #+#             */
/*   Updated: 2019/11/11 20:49:27 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *mem;

	mem = s;
	while (n)
	{
		if (*mem == (unsigned char)c)
			return ((void *)mem);
		mem++;
		n--;
	}
	return (NULL);
}
