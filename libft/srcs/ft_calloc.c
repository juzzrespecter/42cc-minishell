/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:48:34 by danrodri          #+#    #+#             */
/*   Updated: 2019/11/11 20:48:13 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	char	*ptr;
	size_t	i;

	mem = malloc(count * size);
	if (mem == NULL)
		return (NULL);
	i = 0;
	ptr = mem;
	while (i < count * size)
	{
		*mem = 0;
		mem++;
		i++;
	}
	return (ptr);
}
