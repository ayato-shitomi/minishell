#include "../includes/minishell.h"

void	ft_lstinsert_ms(t_info *info, t_token_lst *lst, size_t *i, int type)
{
	size_t		j;
	t_token_lst	*lst_tmp;

	j = 0;
	lst_tmp = info->token_lst->next;
	if (info->token_lst->type == type)
	{
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
		if (info->token_lst->lst_last_flag == 1)
		{
			info->token_lst->lst_last_flag = 0;
			lst->lst_last_flag = 1;
			if (lst_tmp->lst_first_flag == 1 && \
				lst_tmp->next == info->token_lst)
				lst_tmp->next = info->token_lst;
		}
		lst->prev = info->token_lst;
		lst->next = lst_tmp;
		lst_tmp->prev = lst;
		info->token_lst->next = lst;
	}
	else
	{
		info->token_lst->token[*i] = '\0';
		if (info->token_lst->lst_last_flag == 1)
		{
			info->token_lst->lst_last_flag = 0;
			lst->lst_last_flag = 1;
			if (lst_tmp->lst_first_flag == 1 && \
				lst_tmp->next == info->token_lst)
				lst_tmp->next = info->token_lst;
		}
		lst->prev = info->token_lst;
		lst->next = lst_tmp;
		lst_tmp->prev = lst;
		info->token_lst->next = lst;
	}
}
