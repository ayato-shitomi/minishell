/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:21:03 by mhida             #+#    #+#             */
/*   Updated: 2022/07/21 23:40:28 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *dst, const char *src, size_t n)
{
	unsigned char	*dst2;
	unsigned char	*src2;
	size_t			i;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	i = 0;
	while ((i < n) && (dst2[i] != '\0') && (src2[i] != '\0'))
	{
		if (dst2[i] != src2[i])
			return (dst2[i] - src2[i]);
		i++;
	}
	if ((dst2[i] != src2[i]) && (i < n))
		return (dst2[i] - src2[i]);
	return (0);
}

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (n--)
		str[i++] = 0;
}

void	*ft_calloc(size_t n, size_t size)
{
	unsigned char	*heap;
	size_t			i;

	if (size > 0)
		if (n > (size_t)(-1) / size)
			return (NULL);
	i = n * size;
	if (n == 0 || size == 0)
		i = 1;
	heap = (unsigned char *)malloc(i);
	if (!(heap == NULL))
	{
		ft_bzero(heap, i);
		return (heap);
	}
	return (NULL);
}
