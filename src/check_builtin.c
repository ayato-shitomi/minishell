#include "../includes/minishell.h"

static size_t	get_ac_2(t_info *info)
{
	size_t	ac;
	t_lst	*cmd_lst_tmp;

	cmd_lst_tmp = info->sentence_lst->cmd_lst;
	ac = 0;
	while (info->sentence_lst->cmd_lst)
	{
		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
		ac++;
	}
	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	return (ac);
}

static size_t	get_ac(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	exec_builtin_without_pipe(t_info *info) //パイプなしビルトイン実行
{
	int		status;
	size_t	ac;

	status = SUCCESS;
	ac = get_ac_2(info);
	if (ft_strncmp(info->sentence_lst->cmd_lst->str, "cd\0", 3) == 0)
		status = ft_cd(info);
	else if (ft_strncmp(info->sentence_lst->cmd_lst->str, "pwd\0", 4) == 0)
		status = ft_pwd(info);
	else if (ft_strncmp(info->sentence_lst->cmd_lst->str, "exit\0", 5) == 0)
		status = ft_exit(ac, NULL, info->sentence_lst->cmd_lst);
	return (status);
}

int	exec_builtin(t_info *info, char **cmd)
{
	int		status;
	size_t	ac;

	status = SUCCESS;
	ac = get_ac(cmd);
	if (ft_strncmp(cmd[0], "cd\0", 3) == 0)
		status = ft_cd(info);
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		status = ft_pwd(info);
	else if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		status = ft_exit(ac, cmd, NULL);
	return (status);
}

int	check_builtin(char **cmd)
{
	if ((ft_strncmp(cmd[0], "cd\0", 3) == 0) || \
		(ft_strncmp(cmd[0], "pwd\0", 4) == 0) || \
		(ft_strncmp(cmd[0], "exit\0", 5) == 0))
		return (1);
	return (0);
}
