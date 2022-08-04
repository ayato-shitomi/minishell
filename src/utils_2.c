#include "../includes/minishell.h"

static char	*ft_strcat(char *dst, char *src)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = 0;
	while (src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*heap;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	s3_len = ft_strlen((char *)s3);
	heap = (char *)ft_calloc(s1_len + s2_len + s3_len + 1, sizeof(char));
	if (!heap)
		exit(ERROR);
	heap = ft_strcpy(heap, (char *)s1);
	heap = ft_strcat(heap, (char *)s2);
	heap = ft_strcat(heap, (char *)s3);
	return (heap);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!ft_strlen((char *)needle))
		return ((char *)haystack);
	if (ft_strlen(haystack) < ft_strlen(needle))
		return (NULL);
	if ((ft_strncmp(haystack, needle, len) == 0) && len != 0 && \
		len >= ft_strlen(needle))
		return ((char *)haystack);
	i = 0;
	while (i < len)
	{
		if (*haystack == *needle)
		{
			if (len - i < ft_strlen(needle))
				return (NULL);
			if (ft_strncmp(haystack, needle, ft_strlen(needle)) == 0)
				return ((char *)(haystack));
		}
		haystack++;
		i++;
	}
	return (NULL);
}
