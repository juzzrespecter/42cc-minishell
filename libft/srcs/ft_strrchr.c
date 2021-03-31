/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:17:20 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:31:07 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*lstoccr;

	lstoccr = NULL;
	while (*s)
	{
		if (*s == (char)c)
			lstoccr = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	if (lstoccr == NULL)
		return (NULL);
	return ((char *)lstoccr);
}
