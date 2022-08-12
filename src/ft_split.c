#include "../includes/minishell.h"

static size_t	get_cnt(char *str, char c)
{
	size_t	split_len;

	split_len = 0;
	while (*str)
	{
		if ((*str == c) && (str[1] != c))
			split_len++;
		str++;
	}
	return (split_len + 1);
}

static char	*ft_tmp_len(char *s, size_t *len, char *tmp, char c)
{
	while ((*s != '\0') && (*s != c))
		s++;
	*len = (size_t)(s - tmp);
	return (s);
}

static int	ft_alloc_2(char **split, long long *index)
{
	*index = 0;
	if (split == NULL)
	{
		free(split);
		return (0);
	}
	return (1);
}

static long	ft_alloc_1(char **split, char *tmp, long long *index, size_t *len)
{
	size_t	i;

	i = 0;
	split[*index] = (char *)ft_calloc((*len) + 1, sizeof(char));
	if (split[*index] == NULL)
	{
		while (i <= *(size_t *)index)
			free(split[i++]);
		free(split);
		return (-42);
	}
	while (i < *len)
	{
		split[*index][i] = tmp[i];
		i++;
	}
	split[*index][*len] = 0;
	return (*index + 1);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	char		*tmp;
	long long	index;
	size_t		len;

	if (!s)
		return (NULL);
	split = (char **)ft_calloc((get_cnt((char *)s, c) + 1), sizeof(char *));
	if (!ft_alloc_2(&*split, &index))
		exit (ERROR);
	while (*s)
	{
		if (*s != c)
		{
			tmp = (char *)s;
			s = ft_tmp_len((char *)s, &len, tmp, c);
			index = ft_alloc_1(&(*split), tmp, &index, &len);
		}
		if (index == -42)
			exit (ERROR);
		if (*s != '\0')
			s++;
	}
	split[index] = NULL;
	return (split);
}
