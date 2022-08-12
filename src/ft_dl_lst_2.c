#include "../includes/minishell.h"

static void	set_dl_lst_p(t_info *info, t_token_dl_lst *dl_lst, \
	t_token_dl_lst *dl_lst_tmp)
{
	dl_lst->prev = info->token_dl_lst;
	dl_lst->next = dl_lst_tmp;
	dl_lst_tmp->prev = dl_lst;
	info->token_dl_lst->next = dl_lst;
}

static void	check_dl_lst_flag(t_info *info, t_token_dl_lst *dl_lst, \
	t_token_dl_lst *dl_lst_tmp)
{
	if (info->token_dl_lst->dl_lst_last_flag == 1)
	{
		info->token_dl_lst->dl_lst_last_flag = 0;
		dl_lst->dl_lst_last_flag = 1;
		if (dl_lst_tmp->dl_lst_first_flag == 1 && \
			dl_lst_tmp->next == info->token_dl_lst)
			dl_lst_tmp->next = info->token_dl_lst;
	}
}

static int	check_type(t_info *info, size_t *i, int type)
{
	size_t	j;

	j = 0;
	if (type == EXPANDABLE_QUOTED || type == NOT_EXPANDABLE)
	{
		while (j < (*i - 1))
		{
			info->token_dl_lst->token[j] = info->token_dl_lst->token[j + 1];
			j++;
		}
		info->token_dl_lst->token[j] = '\0';
	}
	else if (type == PIPE)
		info->token_dl_lst->token[1] = '\0';
	else if (type == REDIRECT_LEFT_ONE || type == REDIRECT_RIGHT_ONE)
		info->token_dl_lst->token[1] = '\0';
	else if (type == REDIRECT_LEFT_TWO || type == REDIRECT_RIGHT_TWO)
		info->token_dl_lst->token[2] = '\0';
	return (0);
}

void	ft_dl_lstinsert(t_info *info, t_token_dl_lst *dl_lst, size_t *i, \
	int type)
{
	t_token_dl_lst	*dl_lst_tmp;

	dl_lst_tmp = info->token_dl_lst->next;
	if (info->token_dl_lst->type == type)
	{
		check_type(info, i, type);
		check_dl_lst_flag(info, dl_lst, dl_lst_tmp);
		set_dl_lst_p(info, dl_lst, dl_lst_tmp);
	}
	else
	{
		info->token_dl_lst->token[*i] = '\0';
		check_dl_lst_flag(info, dl_lst, dl_lst_tmp);
		set_dl_lst_p(info, dl_lst, dl_lst_tmp);
	}
}

void	ft_dl_lstcat(t_info *info)
{
	char			*token_tmp;
	t_token_dl_lst	*dl_lst_tmp;

	token_tmp = ft_strjoin(info->token_dl_lst->token, \
		info->token_dl_lst->next->token);
	free(info->token_dl_lst->token);
	free(info->token_dl_lst->next->token);
	info->token_dl_lst->token = token_tmp;
	info->token_dl_lst->is_concatenated_with_next = \
		info->token_dl_lst->next->is_concatenated_with_next;
	dl_lst_tmp = info->token_dl_lst->next;
	info->token_dl_lst->next = info->token_dl_lst->next->next;
	info->token_dl_lst->next->prev = info->token_dl_lst;
	free(dl_lst_tmp);
	if (info->token_dl_lst->next->dl_lst_first_flag)
		info->token_dl_lst->dl_lst_last_flag = 1;
}
