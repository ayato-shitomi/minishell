/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:52:18 by mhida             #+#    #+#             */
/*   Updated: 2022/09/14 01:46:27 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_bufcat(char *tmp, char *buf, size_t buf_i)
{
	size_t	tmp_len;
	size_t	i;

	tmp_len = ft_strlen(tmp);
	i = 0;
	while (i < buf_i)
		tmp[tmp_len++] = buf[i++];
	tmp[tmp_len] = '\0';
	return (tmp);
}

size_t	ft_strchr_i(const char *str, int chr, int *flag)
{
	char	*result;
	size_t	i;

	*flag = 0;
	i = 0;
	result = (char *)str;
	while (result[i] != '\0')
	{
		if (result[i] == (char)chr)
			return (i);
		i++;
	}
	return (i);
}
