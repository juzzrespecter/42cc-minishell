/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 18:43:43 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:38:12 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int	ft_get_isize(long int i, int bsize)
{
	int	isize;

	isize = 0;
	while (i)
	{
		i /= bsize;
		isize++;
	}
	return (isize);
}

static char	*ft_rev_a(char *a)
{
	int		a_len;
	int		i;
	char	aux;

	a_len = ft_strlen(a);
	i = 0;
	while (i < a_len / 2)
	{
		aux = a[i];
		a[i] = a[a_len - (i + 1)];
		a[a_len - (i + 1)] = aux;
		i++;
	}
	return (a);
}

static int	ft_check_base(char *base)
{
	int	count;

	count = 0;
	if (!base || ft_strlen(base) == 1)
		return (0);
	while (base[count])
	{
		if (ft_strchr(base + count + 1, base[count]))
			return (0);
		count++;
	}
	return (1);
}

char	*ft_lltoa_base(long long int i, char *base)
{
	char	*a;
	int		count;
	int		b_len;

	if (!ft_check_base(base))
		return (NULL);
	b_len = ft_strlen(base);
	a = malloc(sizeof(char) * (ft_get_isize(i, b_len) + 1));
	if (!a)
		return (NULL);
	count = 0;
	while (i)
	{
		a[count] = base[i % b_len];
		i /= b_len;
		count++;
	}
	a[count] = 0;
	ft_rev_a(a);
	return (a);
}
