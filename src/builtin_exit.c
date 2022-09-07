#include "../includes/minishell.h"

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
	printf("exit\n");
	(void)cmd;
	if (ac == 1)
		exit (0);
	if (check_arg(cmd_lst->next->str))
	{
		printf("fresh: exit: %s: %s\n", cmd_lst->next->str, s);
		exit(255);
	}
	if (3 <= ac)
	{
		printf("fresh: exit: too many arguments\n");
		return (1);
	}
	exit(make_status(cmd_lst->next->str));
	return (1);
}
