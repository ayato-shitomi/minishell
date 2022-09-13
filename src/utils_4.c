/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:28 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_judge(long long *llon, int *sign, int n_len)
{
	long long	tmp;

	*sign = 0;
	tmp = *llon;
	if (*llon < 0)
		*sign = -1;
	if (*llon >= 0 && *llon <= 9)
		n_len = 1;
	else
	{
		while (tmp)
		{
			tmp /= 10;
			n_len++;
		}
		if (*sign == -1)
		{
			*llon *= -1;
			n_len++;
		}
	}
	return (n_len);
}

char	*ft_itoa(int n)
{
	char		*heap;
	int			n_len;
	int			n_len_tmp;
	int			sign;
	long long	llon;

	llon = n;
	n_len = 0;
	n_len = ft_judge(&llon, &sign, n_len);
	n_len_tmp = n_len;
	heap = (char *)malloc(sizeof(char) * (n_len + 1));
	if (heap == NULL)
		return (NULL);
	while (n_len > 0 && !(n_len == 1 && sign == -1))
	{
		if (sign == -1)
			heap[0] = '-';
		heap[n_len - 1] = llon % 10 + '0';
		llon /= 10;
		n_len--;
	}
	heap[n_len_tmp] = '\0';
	return (heap);
}

int	ft_isalnum(int n)
{
	if ((n >= '0' && n <= '9')
		|| (n >= 'A' && n <= 'Z')
		|| (n >= 'a' && n <= 'z'))
		return (1);
	return (0);
}

int	ft_strcmp(const char *dst, const char *src)
{
	unsigned char	*dst2;
	unsigned char	*src2;
	size_t			i;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (!dst2 && !src2)
		return (0);
	else if (dst2 && !src2)
		return (1);
	else if (!dst2 && src2)
		return (-1);
	i = 0;
	while (dst2[i] && src2[i])
	{
		if (dst2[i] != src2[i])
			return (dst2[i] - src2[i]);
		i++;
	}
	if (dst2[i] != src2[i])
		return (dst2[i] - src2[i]);
	return (0);
}
