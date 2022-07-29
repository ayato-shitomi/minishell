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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	if (!dst || !src)
		return (0);
	src_len = ft_strlen((char *)src);
	i = 0;
	if (size == 0)
		return (src_len);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
