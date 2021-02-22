/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:14:54 by danrodri          #+#    #+#             */
/*   Updated: 2021/02/22 17:18:03 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_newline(char *str)
{
	int	nl_pos;

	nl_pos = 0;
	while (str[nl_pos])
	{
		if (str[nl_pos] == '\n')
			return (nl_pos);
		nl_pos++;
	}
	return (-1);
}

static void	remove_lines(char *lines[FD_SETSIZE], int fd)
{
	ft_bzero(lines[fd], BUFFER_SIZE + 1);
	free(lines[fd]);
	lines[fd] = NULL;
}

static int	save_line(int fd, char **line, char *lines[FD_SETSIZE], char *buff)
{
	int		nl_pos;
	char	buff_aux[BUFFER_SIZE + 1];
	char	*mem_free;

	mem_free = *line;
	if ((nl_pos = find_newline(buff)) != -1)
	{
		if (!lines[fd])
			if (!(lines[fd] = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
				return (0);
		ft_strlcpy(lines[fd], buff + nl_pos + 1, BUFFER_SIZE - nl_pos);
		ft_strlcpy(buff_aux, buff, nl_pos + 1);
		*line = ft_strjoin(*line, buff_aux);
		if (!*lines[fd])
			remove_lines(lines, fd);
	}
	else
	{
		*line = ft_strjoin(*line, buff);
		if (lines[fd])
			remove_lines(lines, fd);
	}
	free(mem_free);
	return (*line ? 1 : 0);
}

static int	read_line(int fd, char **line, char *lines[FD_SETSIZE])
{
	int		nl_pos;
	char	buffer[BUFFER_SIZE + 1];
	int		r_out;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	while ((nl_pos = find_newline(buffer)) == -1)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		r_out = read(fd, buffer, BUFFER_SIZE);
		if (!r_out)
			return (0);
		if (r_out < 0)
			return (-1);
		if (!save_line(fd, line, lines, buffer))
			return (-1);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	*lines[FD_SETSIZE] = {0};
	char		buff_aux[BUFFER_SIZE + 1];
	int			nl_pos;

	if (fd < 0 || !line || !BUFFER_SIZE)
		return (-1);
	if (!(*line = ft_strdup("")))
		return (-1);
	if (lines[fd])
	{
		free(*line);
		if ((nl_pos = find_newline(lines[fd])) >= 0)
		{
			ft_strlcpy(buff_aux, lines[fd], nl_pos + 1);
			ft_strlcpy(lines[fd], lines[fd] + nl_pos + 1, BUFFER_SIZE - nl_pos);
			*line = ft_strdup(buff_aux);
			if (!*lines[fd])
				remove_lines(lines, fd);
			return (*line ? 1 : -1);
		}
		if (!(*line = ft_strdup(lines[fd])))
			return (-1);
		remove_lines(lines, fd);
	}
	return (read_line(fd, line, lines));
}
