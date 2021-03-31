/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:54:29 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:33:53 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_lenstr(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static char	*ft_cpystr(const char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

char	*ft_strdup(const char *s1)
{
	char			*copy;

	copy = malloc(sizeof(char) * (ft_lenstr(s1) + 1));
	if (!copy)
		return (NULL);
	copy = ft_cpystr(s1, copy);
	return (copy);
}
