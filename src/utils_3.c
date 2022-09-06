#include "../includes/minishell.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		pm;

	if (!(ft_strcmp(str, "-9223372036854775809")))
		return (0);
	i = 0;
	num = 0;
	pm = 1;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pm = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num > (LONG_MAX - (str[i] - '0')) / 10 && pm == 1)
			return (-1);
		if ((num + ((str[i] - '0') / 10)) * pm < LONG_MIN / 10 && pm == -1)
			return (0);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * pm);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > INT_MAX)
	{
		write(fd, s, INT_MAX);
		s += INT_MAX;
		len -= INT_MAX;
	}
	write(fd, s, len);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

char	*ft_strchr(const char *str, int chr)
{
	char	*result;
	size_t	i;

	i = 0;
	result = (char *)str;
	while (result[i] != '\0')
	{
		if (result[i] == (char)chr)
			return (&result[i]);
		i++;
	}
	if (chr == '\0')
		return (&result[i]);
	return (NULL);
}
