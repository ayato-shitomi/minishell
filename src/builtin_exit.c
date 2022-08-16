#include "../includes/minishell.h"

static int	make_status(char *str)
{
	int	n;
	
	if (!(ft_strncmp(str, "-9223372036854775809", 20)))
		return (255);
	n = ft_atoi((const char)str);
	if (n == 0)
		return (0);
	return (n % 256);
}

void	ft_exit(int argc, char *argv[])
{
	printf("exit\n");
	if (argc != 1)
		printf("fresh: exit: too many arguments\n");
	if (!argv[0])
		exit(0);
	status = make_status(argv[1]);
	exit(status);
}

