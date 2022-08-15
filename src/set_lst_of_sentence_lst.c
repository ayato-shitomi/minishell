#include "../includes/minishell.h"

static int	set_lst_case_branch(t_info *info, int flag)
{
	t_lst			*lst;

	while (info->token_dl_lst->is_cat_with_next)
		ft_dl_lstcat(info);
	lst = ft_lstnew(info->token_dl_lst->token);
	set_lst_info(info, lst, flag);
	check_env_var_and_set_env_var_info(info, lst);
	if (flag == REDIRECT_LST)
		ft_lstadd_back(&(info->sentence_lst->redirect_lst), lst);
	else if (flag == CMD_LST)
		ft_lstadd_back(&(info->sentence_lst->cmd_lst), lst);
	return (flag);
}

static int	check_token_type_and_case_branch(t_info *info, int *flag)
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
	while (info->sentence_lst)
	{
		flag = CMD_LST;
		while (1)
		{
			if (check_token_type_and_case_branch(info, &flag) == 1)
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
