/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:50:38 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 16:35:59 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_check_spaces(char c)
{
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	if (c == '\v')
		return (1);
	if (c == '\f')
		return (1);
	if (c == '\r')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	negativo;

	negativo = 0;
	n = 0;
	while (ft_check_spaces(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negativo++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	if (negativo == 1)
		n *= -1;
	return (n);
}
