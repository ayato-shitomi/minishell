#include "../includes/minishell.h"

static char	**set_buf_in_cmd_lst(t_info *info, char **cmd)
{
	size_t	i;
	size_t	cmd_lst_cnt;
	size_t	len;
	t_lst	*cmd_lst_tmp;

	cmd_lst_tmp = info->sentence_lst->cmd_lst;
	cmd_lst_cnt = ft_lstsize(info->sentence_lst->cmd_lst);
	cmd = (char **)ft_calloc(cmd_lst_cnt + 1, sizeof(char *));
	if (!cmd)
		exit(ERROR);
	i = 0;
	while (i < cmd_lst_cnt)
	{
		len = ft_strlen(info->sentence_lst->cmd_lst->str);
		cmd[i] = (char *)ft_calloc(len + 1, sizeof(char));
		if (!cmd[i])
			exit(ERROR);
		ft_strcpy(cmd[i], info->sentence_lst->cmd_lst->str);
		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
		i++;
	}
	cmd[i] = NULL;
	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	return (cmd);
}

static void	change_lst_p(t_info *info, t_lst *cmd_lst_tmp, \
	t_lst *redirect_lst_tmp, t_lst *env_var_lst_tmp)
{
	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	info->sentence_lst->redirect_lst = redirect_lst_tmp;
	info->sentence_lst->env_var_lst = env_var_lst_tmp;
	info->sentence_lst = info->sentence_lst->next;
}

static void	set_lst_tmp(t_info *info, t_lst **cmd_lst_tmp, \
	t_lst **redirect_lst_tmp, t_lst **env_var_lst_tmp)
{
	*cmd_lst_tmp = info->sentence_lst->cmd_lst;
	*redirect_lst_tmp = info->sentence_lst->redirect_lst;
	*env_var_lst_tmp = info->sentence_lst->env_var_lst;
}

int	execute_command(t_info *info)
{
	//コマンド実行用関数
	char			**cmd;
	t_sentence_lst	*sentence_lst_tmp;
	t_lst			*cmd_lst_tmp;
	t_lst			*redirect_lst_tmp;
	t_lst			*env_var_lst_tmp;

	cmd = NULL;
	sentence_lst_tmp = info->sentence_lst;
	while (info->sentence_lst)
	{
		set_lst_tmp(info, &cmd_lst_tmp, &redirect_lst_tmp, &env_var_lst_tmp);
		cmd = set_buf_in_cmd_lst(info, cmd);
		// int	i = 0;
		// while (cmd[i])
		// {
		// 	printf("cmd[i] = %s\n", cmd[i++]);
		// }
		set_fd_by_redirect_lst(info, cmd);
		change_lst_p(info, cmd_lst_tmp, redirect_lst_tmp, env_var_lst_tmp);
	}
	info->sentence_lst = sentence_lst_tmp;
	return (SUCCESS);
}
