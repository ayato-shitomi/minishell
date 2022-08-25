#include "../includes/minishell.h"

static int	make_status(char *str)
{
	int	n;

	if (!(ft_strncmp(str, "-9223372036854775809", 20)))
		return (255);
	n = ft_atoi((const char *)str);
	if (n == 0)
		return (0);
	return (n % 256);
}

// void	ft_exit(int argc, char *argv[])
int	ft_exit(size_t ac, char **cmd, t_lst *cmd_lst)
{
	int	status;

	status = SUCCESS;
	if (cmd)
	{
		printf("exit\n");
		if (ac >= 3)
			printf("fresh: exit: too many arguments\n");
		if (!cmd[1])
			exit(0);
		status = make_status(cmd[1]);
	}
	else if (cmd_lst)
	{
		printf("exit\n");
		if (ac >= 3)
		{
			printf("fresh: exit: too many arguments\n");
			exit(ERROR);
		}
		else if (cmd_lst->next)
		{
			status = make_status(cmd_lst->next->str);
			exit(status);
		}
	}
	exit(status);
}
