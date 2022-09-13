/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lst_of_sentence_lst.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:28 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	set_lst_case_branch(t_info *info, int flag, int is_first_sentence) // ⑦
{
	t_lst			*lst;
	int				continue_flag;
	int				flag_quote_after_env;
	int				env_set_flag;

	continue_flag = 1;
	flag_quote_after_env = 0;
	lst = NULL;
	while (continue_flag)
	{
		continue_flag = 0;
		env_set_flag = 1;
		while (info->token_dl_lst->is_cat_with_next)
		{
			if ((info->token_dl_lst->next->type == EXPANDABLE_QUOTED || info->token_dl_lst->next->type == NOT_EXPANDABLE) \
				&& (ft_strchr(info->token_dl_lst->token, '$') && info->token_dl_lst->type != NOT_EXPANDABLE) && flag_quote_after_env == 0)
			{
				continue_flag = 1;
				flag_quote_after_env = 1;
				break ;
			}
			else
			{
				ft_dl_lstcat(info);
				if (flag_quote_after_env)
				{
					flag_quote_after_env = 0;
					env_set_flag = 0;
					break ;
				}
			}
		}
		if (lst)
			free(lst);
		lst = ft_lstnew(info->token_dl_lst->token);
		set_lst_info(info, lst, flag);
		if (env_set_flag)
			check_env_var_and_set_env_var_info(info, lst, is_first_sentence); // ⑧
	}
	if (flag == REDIRECT_LST)
		ft_lstadd_back(&(info->sentence_lst->redirect_lst), lst);
	else if (flag == CMD_LST)
		ft_lstadd_back(&(info->sentence_lst->cmd_lst), lst);
	return (flag);
}

static int	check_token_type_and_case_branch(t_info *info, int *flag, int is_first_sentence) // ④
{
	if (info->token_dl_lst->type == PIPE)
	{
		info->token_dl_lst = info->token_dl_lst->next;
		return (1);
	}
	else if ((info->token_dl_lst->type >= REDIRECT_LEFT_ONE && \
		info->token_dl_lst->type <= REDIRECT_RIGHT_TWO) || \
		*flag == REDIRECT_LST)
		*flag = set_lst_case_branch(info, REDIRECT_LST, is_first_sentence);
	else
		*flag = set_lst_case_branch(info, CMD_LST, is_first_sentence);
	return (0);
}

void	set_lst_of_sentence_lst(t_info *info)
{
	int				flag;
	int				is_first_sentence; // ①
	t_sentence_lst	*sentence_lst_tmp;

	sentence_lst_tmp = info->sentence_lst;
	is_first_sentence = 1;
	while (info->sentence_lst)
	{
		flag = CMD_LST;
		while (1)
		{
			if (check_token_type_and_case_branch(info, &flag, is_first_sentence) == 1) // ③
				break ;
			info->token_dl_lst = info->token_dl_lst->next;
			if (info->token_dl_lst->dl_lst_first_flag == 1)
				break ;
		}
		if (info->token_dl_lst->dl_lst_first_flag == 1)
			break ;
		if (is_first_sentence) // ②
			is_first_sentence = 0;
		info->sentence_lst = info->sentence_lst->next;
	}
	info->sentence_lst = sentence_lst_tmp;
}
