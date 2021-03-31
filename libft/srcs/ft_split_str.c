/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:44:55 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 18:55:33 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sep_len(char *sep, char *s)
{
	int	len;

	len = 0;
	while (ft_strrchr(sep, s[len]))
		len++;
	return (len);
}

static int	str_len(char *s, char *sep)
{
	int	len;

	len = 0;
	while (s[len] && !ft_strrchr(sep, s[len]))
		len++;
	return (len);
}

static int	dst_len(char *s, char *sep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		i += sep_len(sep, s);
		if (s[i] && !ft_strrchr(sep, s[i]))
			len++;
		i += str_len(sep, s);
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

char	**ft_split_str(char *s, char *sep)
{
	char	**dst;
	int		pos;
	int		i;

	if (!s || !sep)
		return (NULL);
	dst = (char **)malloc(sizeof(char *) * (dst_len(s, sep) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	pos = 0;
	while (s[i])
	{
		i += sep_len(sep, s);
		if (!ft_strrchr(sep, s[i]))
		{
			dst[pos] = ft_substr(s, i, str_len(s + i, sep));
			if (!dst[pos])
				return (free_dst(dst));
			pos++;
		}
		i += str_len(sep, s);
	}
	dst[pos] = NULL;
	return (dst);
}
