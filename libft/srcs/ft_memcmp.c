/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:30:59 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:41:45 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*mems1;
	const unsigned char	*mems2;
	size_t				i;

	mems1 = s1;
	mems2 = s2;
	i = 0;
	while (i < n)
	{
		if (mems1[i] != mems2[i])
			return (mems1[i] - mems2[i]);
		i++;
	}
	return (0);
}
