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
