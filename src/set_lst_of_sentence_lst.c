/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lst_of_sentence_lst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/16 13:43:46 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	loop_to_cat(t_info *info, t_lst *lst)
{
	char			*tmp_str;

	while (info->token_dl_lst->is_cat_with_next)
	{
		tmp_str = lst->str;
		lst->str = ft_strjoin(lst->str, info->token_dl_lst->next->token);
		free(tmp_str);
		info->token_dl_lst = info->token_dl_lst->next;
	}
}

static int	set_lst_case_branch(t_info *info, int lst_type)
{
	t_lst			*lst;

	lst = ft_lstnew(info->token_dl_lst->token);
	set_lst_info(info, lst, lst_type);
	loop_to_cat(info, lst);
	if (lst_type == REDIRECT_LST)
		ft_lstadd_back(&(info->sentence_lst->redirect_lst), lst);
	else if (lst_type == CMD_LST)
		ft_lstadd_back(&(info->sentence_lst->cmd_lst), lst);
	return (lst_type);
}

static int	chk_tkntype_case_branch(t_info *info, int *flag)
{
	if (info->token_dl_lst->type == PIPE)
	{
		info->token_dl_lst = info->token_dl_lst->next;
		return (1);
	}
	else if ((info->token_dl_lst->type >= REDIRECT_LEFT_ONE && \
		info->token_dl_lst->type <= REDIRECT_RIGHT_TWO) || \
		*flag == REDIRECT_LST)
		*flag = set_lst_case_branch(info, REDIRECT_LST);
	else
		*flag = set_lst_case_branch(info, CMD_LST);
	return (0);
}

void	set_lst_of_sentence_lst(t_info *info)
{
	int				flag;
	t_sentence_lst	*sentence_lst_tmp;

	sentence_lst_tmp = info->sentence_lst;
	check_env_var_and_set_env_var_info(info);
	info->sentence_lst = sentence_lst_tmp;
	while (info->sentence_lst)
	{
		flag = CMD_LST;
		while (1)
		{
			if (chk_tkntype_case_branch(info, &flag) == 1)
				break ;
			info->token_dl_lst = info->token_dl_lst->next;
			if (info->token_dl_lst->dl_lst_first_flag == 1)
				break ;
		}
		if (info->token_dl_lst->dl_lst_first_flag == 1)
			break ;
		info->sentence_lst = info->sentence_lst->next;
	}
	info->sentence_lst = sentence_lst_tmp;
}
