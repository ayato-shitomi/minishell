/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/16 13:19:48 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	expand_env_var_in_redirect_lst(t_info *info)
{
	while (info->sentence_lst->redirect_lst)
	{
		if (expand_the_expandable_in_redirect_lst(info) == 1)
			return ;
		info->sentence_lst->redirect_lst = \
			info->sentence_lst->redirect_lst->next;
	}
}

static void	expand_env_var_in_cmd_lst(t_info *info)
{
	while (info->sentence_lst->cmd_lst)
	{
		if (expand_the_expandable_in_cmd_lst(info) == 1)
			return ;
		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
	}
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

void	expand_env_var(t_info *info)
{
	t_sentence_lst	*sentence_lst_tmp;
	t_lst			*cmd_lst_tmp;
	t_lst			*redirect_lst_tmp;
	t_lst			*env_var_lst_tmp;

	sentence_lst_tmp = info->sentence_lst;
	while (info->sentence_lst)
	{
		set_lst_tmp(info, &cmd_lst_tmp, &redirect_lst_tmp, &env_var_lst_tmp);
		expand_env_var_in_cmd_lst(info);
		expand_env_var_in_redirect_lst(info);
		change_lst_p(info, cmd_lst_tmp, redirect_lst_tmp, env_var_lst_tmp);
	}
	info->sentence_lst = sentence_lst_tmp;
}
