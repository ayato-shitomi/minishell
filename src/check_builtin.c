#include "../includes/minishell.h"

static size_t	get_ac(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	check_builtin(char **cmd)
{
	size_t	cmd_len;
	size_t	ac;

	ac = get_ac(cmd);
	cmd_len = ft_strlen(cmd[0]);
	if (ft_strncmp(cmd[0], "cd", 2) == 0 && cmd_len == 2)
		ft_cd(cmd[1]);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0 && cmd_len == 3)
		ft_pwd();
	else if (ft_strncmp(cmd[0], "exit", 4) == 0 && cmd_len == 4)
		ft_exit(ac, cmd);
}
