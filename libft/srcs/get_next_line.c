/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:14:54 by danrodri          #+#    #+#             */
/*   Updated: 2021/03/31 20:02:07 by danrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_next_backup(int fd, char **line, char **backup)
{
	if (fd < 0 || !line || !BUFFER_SIZE)
		return (-1);
	if (backup[fd])
	{
		*line = ft_strdup(backup[fd]);
		ft_bzero(backup[fd], ft_strlen(backup[fd]));
		free(backup[fd]);
		backup[fd] = NULL;
	}
	else
		*line = ft_strdup("");
	if (!*line)
		return (-1);
	return (0);
}

static int	free_and_exit(char *str)
{
	free (str);
	return (-1);
}

static int	get_out(int fd, char **line, char **backup, char *nl_pos)
{
	if (**line == 0)
		return (0);
	if (nl_pos != NULL)
	{
		backup[fd] = ft_strdup(nl_pos + 1);
		if (!backup[fd])
			return (free_and_exit(*line));
		ft_bzero(nl_pos, ft_strlen(nl_pos));
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*backup[FD_SETSIZE] = {0};
	char		buffer[BUFFER_SIZE + 1];
	int			func_ret;
	char		*nl_pos;

	func_ret = get_next_backup(fd, line, backup);
	if (func_ret == -1)
		return (-1);
	nl_pos = ft_strchr(*line, '\n');
	while (nl_pos == NULL)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		func_ret = read(fd, buffer, BUFFER_SIZE);
		if (func_ret < 0)
			return (free_and_exit(*line));
		if (func_ret == 0)
			break ;
		nl_pos = *line;
		*line = ft_strjoin(*line, buffer);
		if (!*line)
			return (free_and_exit(nl_pos));
		free(nl_pos);
		nl_pos = ft_strchr(*line, '\n');
	}
	return (get_out(fd, line, backup, nl_pos));
}
