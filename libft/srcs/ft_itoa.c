/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:40:28 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:36:57 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	ft_nlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

static int	ft_nget(int i, int len, int n)
{
	int	div;

	div = 1;
	while (i < len - 1)
	{
		div *= 10;
		i++;
	}
	n /= div;
	return (n % 10 + '0');
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_nlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		n *= -1;
		str[i] = '-';
		i++;
	}
	while (i < len)
	{
		str[i] = ft_nget(i, len, n);
		i++;
	}
	str[i] = 0;
	return (str);
}
