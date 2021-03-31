/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:02:29 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:42:33 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*sdst;
	const unsigned char	*ssrc;

	sdst = dst;
	ssrc = src;
	while (n)
	{
		if (*ssrc == (unsigned char)c)
		{
			*sdst = *ssrc;
			return (sdst + 1);
		}
		*sdst = *ssrc;
		ssrc++;
		sdst++;
		n--;
	}
	return (NULL);
}
