#include "../includes/minishell.h"

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
	t_sentence_lst	*sentence_lst_tmp;
	t_lst			*cmd_lst_tmp;
	t_lst			*redirect_lst_tmp;
	t_lst			*env_var_lst_tmp;

	sentence_lst_tmp = info->sentence_lst;
	while (info->sentence_lst)
	{
		set_lst_tmp(info, &cmd_lst_tmp, &redirect_lst_tmp, &env_var_lst_tmp);
		// set_buf_in_cmd_lst(info);
		change_lst_p(info, cmd_lst_tmp, redirect_lst_tmp, env_var_lst_tmp);
	}
	info->sentence_lst = sentence_lst_tmp;
	return (SUCCESS);
}
