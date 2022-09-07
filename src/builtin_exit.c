#include "../includes/minishell.h"

static void	put_std_err(char *str)
{
	int	n;

	n = ft_strlen(str);
	write(2, str, n);
	return ;
}

static int	make_status(char *str)
{
	int	n;

	if (!(ft_strcmp(str, "-9223372036854775809")))
		return (255);
	n = ft_atoi((const char *)str);
	if (n == 0)
		return (0);
	return (n % 256);
}

static int	check_arg(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (!('0' <= str[n] && str[n] <= '9'))
			return (1);
		n++;
	}
	return (0);
}

int	ft_exit(size_t ac, char **cmd, t_lst *cmd_lst)
{
	char	*s;

	s = "numeric argument required";
	put_std_err("exit\n");
	(void)cmd;
	if (ac == 1)
		exit (0);
	if (check_arg(cmd_lst->next->str))
	{
		put_std_err("fresh: exit: ");
		put_std_err(cmd_lst->next->str);
		put_std_err(": ");
		put_std_err(s);
		put_std_err("\n");
		exit(255);
	}
	if (3 <= ac)
	{
		put_std_err("fresh: exit: too many arguments\n");
		return (1);
	}
	exit(make_status(cmd_lst->next->str));
	return (1);
}
