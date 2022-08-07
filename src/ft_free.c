#include "../includes/minishell.h"

static void	ft_free_sentence_lst_case_branch(t_info *info, int flag)
{
	t_lst			*lst_tmp;

	if (flag == CMD_LST)
	{
		lst_tmp = info->sentence_lst->cmd_lst;
		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
		free(lst_tmp);
	}
	else if (flag == REDIRECT_LST)
	{
		lst_tmp = info->sentence_lst->redirect_lst;
		info->sentence_lst->redirect_lst = \
			info->sentence_lst->redirect_lst->next;
		free(lst_tmp);
	}
	else if (flag == ENV_VAR_LST)
	{
		lst_tmp = info->sentence_lst->env_var_lst;
		free(info->sentence_lst->env_var_lst->key);
		info->sentence_lst->env_var_lst = info->sentence_lst->env_var_lst->next;
		free(lst_tmp);
	}
}

void	ft_free_sentence_lst(t_info *info)
{
	t_sentence_lst	*sentence_lst_tmp;

	while (info->sentence_lst)
	{
		sentence_lst_tmp = info->sentence_lst;
		while (info->sentence_lst->cmd_lst)
			ft_free_sentence_lst_case_branch(info, CMD_LST);
		while (info->sentence_lst->redirect_lst)
			ft_free_sentence_lst_case_branch(info, REDIRECT_LST);
		while (info->sentence_lst->env_var_lst)
			ft_free_sentence_lst_case_branch(info, ENV_VAR_LST);
		info->sentence_lst = info->sentence_lst->next;
		free(sentence_lst_tmp);
	}
}

void	ft_free_p(char *str_env_value_p, char *str_front_p, char *str_back_p, \
	char *str_p)
{
	str_env_value_p = NULL;
	str_front_p = NULL;
	str_back_p = NULL;
	str_p = NULL;
	free(str_env_value_p);
	free(str_front_p);
	free(str_back_p);
	free(str_p);
}

void	ft_free_token_dl_lst(t_info *info)
{
	size_t	i;
	size_t	dl_lstsize;

	if (!(info->token_dl_lst))
		return ;
	i = 0;
	dl_lstsize = ft_dl_lstsize(info->token_dl_lst);
	while (1)
	{
		free(info->token_dl_lst->token);
		info->token_dl_lst = info->token_dl_lst->next;
		if (info->token_dl_lst->dl_lst_first_flag == 1)
		{
			while (i++ < dl_lstsize)
			{
				if (info->token_dl_lst->dl_lst_last_flag == 1)
				{
					free(info->token_dl_lst);
					return ;
				}
				info->token_dl_lst = info->token_dl_lst->next;
				free(info->token_dl_lst->prev);
			}
		}
	}
}
