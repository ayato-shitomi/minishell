/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:51:13 by mhida             #+#    #+#             */
/*   Updated: 2022/08/09 01:12:32 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_malloc_etc(char **line, char **buf, int *flag)
{
	*flag = 0;
	*line = (char *)malloc(1);
	if (!*line)
		return (-1);
	*line[0] = '\0';
	*buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!*buf)
	{
		free(*line);
		return (-1);
	}
	return (1);
}

static void	ft_check_flag(int flag, char **stock, char **line, char **buf)
{
	free(*buf);
	if (flag == -1)
	{
		*stock = NULL;
		free(*line);
	}
}

static int	ft_buf_to_line(char **line, char **stock, char *buf)
{
	char	*tmp;
	size_t	line_len;
	size_t	buf_i;
	int		flag;

	line_len = ft_strlen(*line);
	buf_i = ft_strchr_i(buf, '\n', &flag);
	tmp = (char *)malloc(sizeof(char) * (line_len + buf_i + 1) + 1);
	if (!tmp)
		return (-1);
	tmp = ft_strcpy(tmp, *line);
	tmp = ft_bufcat(tmp, buf, buf_i);
	free(*line);
	*line = tmp;
	tmp = NULL;
	if (buf[buf_i] == '\n')
	{
		tmp = ft_strdup(buf + buf_i + 1);
		if (!tmp)
			return (-1);
		flag = 1;
	}
	free(*stock);
	*stock = tmp;
	return (flag);
}

int	get_next_line(int fd, char **line)
{
	static char	*stock[256];
	char		*buf;
	int			flag;
	ssize_t		n;

	if (fd < 0 || !line || fd >= 256 || BUFFER_SIZE <= 0)
		return (-1);
	if (ft_malloc_etc(line, &buf, &flag) == -1)
		return (-1);
	if (stock[fd])
		flag = ft_buf_to_line(line, &stock[fd], stock[fd]);
	n = 0;
	if (flag == 0)
		n = read(fd, buf, BUFFER_SIZE);
	while (n > 0 && flag == 0)
	{
		buf[n] = '\0';
		flag = ft_buf_to_line(line, &stock[fd], buf);
		if (flag == 0)
			n = read(fd, buf, BUFFER_SIZE);
	}
	ft_check_flag(flag, &stock[fd], line, &buf);
	if (n == -1)
		return (-1);
	return (flag);
}
