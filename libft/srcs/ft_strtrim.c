/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:52:36 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:30:53 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_setmatch(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_rtrim(char const *s1, char const *set)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	i = ft_strlen(s1) - 1;
	while (i > 0 && ft_setmatch(s1[i], set))
	{
		i--;
		r++;
	}
	return (r);
}

static size_t	ft_ltrim(char const *s1, char const *set)
{
	int	l;

	l = 0;
	while (s1[l] && ft_setmatch(s1[l], set))
		l++;
	return (l);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char				*str;
	unsigned int		l;
	unsigned int		r;
	size_t				len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	r = ft_rtrim(s1, set);
	l = ft_ltrim(s1, set);
	len = ft_strlen(s1) - l - r;
	if (ft_strlen(s1) == l)
		return (ft_strdup(""));
	str = ft_substr(s1, l, len);
	return (str);
}
