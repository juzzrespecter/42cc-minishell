/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:44:55 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/05 16:29:37 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dst_len(char *s, char *sep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (ft_strrchr(sep, s[i]))
			i++;
		if (s[i] && !ft_strrchr(sep, s[i]))
			len++;
		while (s[i] && !ft_strrchr(sep, s[i]))
			i++;
	}
	return (len);
}

static char	**free_dst(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
	{
		free(dst[i]);
		i++;
	}
	free(dst);
	return (NULL);
}

static int	str_len(char *s, char *sep)
{
	int	len;

	len = 0;	
	while (s[len] && !ft_strrchr(sep, s[len]))
		len++;
	return (len);
}

char		**ft_split_str(char *s, char *sep)
{
	char	**dst;
	int		pos;
	int		i;

	if (!s || !sep)
		return (NULL);
	if (!(dst = (char **)malloc(sizeof(char *) * (dst_len(s, sep) + 1))))
		return (NULL);
	i = 0;
	pos = 0;
	while (s[i])
	{
		while (ft_strrchr(sep, s[i]))
			i++;
		if (!ft_strrchr(sep, s[i]))
		{
			if (!(dst[pos] = ft_substr(s, i, str_len(s + i, sep))))
				return (free_dst(dst));
			pos++;
		}
		while (!ft_strrchr(sep, s[i]))
			i++;
	}
	dst[pos] = NULL;
	return (dst);
}
