/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:45:36 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:42:09 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*mem;

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
