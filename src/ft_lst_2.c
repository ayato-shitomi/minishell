#include "../includes/minishell.h"

static void	set_lst_p(t_info *info, t_token_lst *lst, t_token_lst *lst_tmp)
{
	lst->prev = info->token_lst;
	lst->next = lst_tmp;
	lst_tmp->prev = lst;
	info->token_lst->next = lst;
}

static void	check_lst_flag(t_info *info, t_token_lst *lst, \
	t_token_lst *lst_tmp)
{
	if (info->token_lst->lst_last_flag == 1)
	{
		info->token_lst->lst_last_flag = 0;
		lst->lst_last_flag = 1;
		if (lst_tmp->lst_first_flag == 1 && \
			lst_tmp->next == info->token_lst)
			lst_tmp->next = info->token_lst;
	}
}

static void	check_type(t_info *info, size_t *i, int type)
{
	size_t	j;

	j = 0;
	if (type == EXPANDABLE_QUOTED || type == NOT_EXPANDABLE)
	{
		while (j < (*i - 1))
		{
			info->token_lst->token[j] = info->token_lst->token[j + 1];
			j++;
		}
		info->token_lst->token[j] = '\0';
	}
	else if (type == PIPE)
		info->token_lst->token[1] = '\0';
	else if (type == REDIRECT_LEFT_ONE || type == REDIRECT_RIGHT_ONE)
		info->token_lst->token[1] = '\0';
	else if (type == REDIRECT_LEFT_TWO || type == REDIRECT_RIGHT_TWO)
		info->token_lst->token[2] = '\0';
}

void	ft_lstinsert_ms(t_info *info, t_token_lst *lst, size_t *i, int type)
{
	t_token_lst	*lst_tmp;

	lst_tmp = info->token_lst->next;
	if (info->token_lst->type == type)
	{
		check_type(info, i, type);
		check_lst_flag(info, lst, lst_tmp);
		set_lst_p(info, lst, lst_tmp);
	}
	else
	{
		info->token_lst->token[*i] = '\0';
		check_lst_flag(info, lst, lst_tmp);
		set_lst_p(info, lst, lst_tmp);
	}
}
