#include "../includes/minishell.h"

// static size_t	get_cnt(char *str, t_info *info)
// {
// 	size_t	split_len;

// 	split_len = 0;
// 	while (*str)
// 	{
// 		quote_check(*str, info);
// 		if ((*str == ' ') && (str[1] != ' ') && \
// 			(info->is_in_dquote == 0 && info->is_in_squote == 0))
// 			split_len++;
// 		str++;
// 	}
// 	init_quote_flag(info);
// 	return (split_len + 1);
// }

// static char	*ft_tmp_len(char *s, size_t *len, char *tmp, t_info *info)
// {
// 	while (*s != '\0')
// 	{
// 		quote_check(*s, info);
// 		if ((info->is_in_dquote == 0 && info->is_in_squote == 0) && *s == ' ')
// 			break ;
// 		s++;
// 	}
// 	init_quote_flag(info);
// 	*len = (size_t)(s - tmp);
// 	return (s);
// }

// static int	ft_alloc_2(char **split, long long *index)
// {
// 	*index = 0;
// 	if (split == NULL)
// 	{
// 		free(split);
// 		return (0);
// 	}
// 	return (1);
// }

// static long	ft_alloc_1(char **split, char *tmp, long long *index, size_t *len)
// {
// 	size_t	i;

// 	i = 0;
// 	split[*index] = (char *)ft_calloc((*len) + 1, sizeof(char));
// 	*split[*index] = 0;
// 	if (split[*index] == NULL)
// 	{
// 		while (i <= *(size_t *)index)
// 			free(split[i++]);
// 		free(split);
// 		return (-42);
// 	}
// 	while (i < *len)
// 	{
// 		split[*index][i] = tmp[i];
// 		i++;
// 	}
// 	split[*index][*len] = 0;
// 	return (*index + 1);
// }

// char	**ft_split_ms(char const *s, t_info *info)
// {
// 	char		**split;
// 	char		*tmp;
// 	long long	index;
// 	size_t		len;

// 	if (!s)
// 		return (NULL);
// 	split = (char **)ft_calloc((get_cnt((char *)s, info) + 1), sizeof(char *));
// 	if (!ft_alloc_2(&*split, &index))
// 		exit (ERROR);
// 	while (*s)
// 	{
// 		if (*s != ' ')
// 		{
// 			tmp = (char *)s;
// 			s = ft_tmp_len((char *)s, &len, tmp, info);
// 			index = ft_alloc_1(&(*split), tmp, &index, &len);
// 		}
// 		if (index == -42)
// 			exit (ERROR);
// 		if (*s != '\0')
// 			s++;
// 	}
// 	split[index] = NULL;
// 	return (split);
// }

static size_t	get_cnt(char *str)
{
	size_t	split_len;

	split_len = 0;
	while (*str)
	{
		if ((*str == ' ') && (str[1] != ' '))
			split_len++;
		str++;
	}
	return (split_len + 1);
}

static char	*ft_tmp_len(char *s, size_t *len, char *tmp)
{
	while ((*s != '\0') && (*s != ' '))
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

char	**ft_split_ms(char const *s)
{
	char		**split;
	char		*tmp;
	long long	index;
	size_t		len;

	if (!s)
		return (NULL);
	split = (char **)ft_calloc((get_cnt((char *)s) + 1), sizeof(char *));
	if (!ft_alloc_2(&*split, &index))
		exit (ERROR);
	while (*s)
	{
		if (*s != ' ')
		{
			tmp = (char *)s;
			s = ft_tmp_len((char *)s, &len, tmp);
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
