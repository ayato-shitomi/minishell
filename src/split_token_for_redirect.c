#include "../includes/minishell.h"

static void	insert_split_token_for_redirect(t_info *info, size_t *i)
{
	size_t		j;
	size_t		len;
	t_token_lst	*lst_tmp;
	char		*token;

	if (info->token_lst->type == REDIRECT_LEFT_ONE || \
		info->token_lst->type == REDIRECT_RIGHT_ONE)
		len = ft_strlen(info->token_lst->token + *i + 1);
	else if (info->token_lst->type == REDIRECT_LEFT_TWO || \
		info->token_lst->type == REDIRECT_RIGHT_TWO)
		len = ft_strlen(info->token_lst->token + *i + 2);
	else
		len = ft_strlen(info->token_lst->token + *i);
	token = (char *)ft_calloc(len + 1, sizeof(char));
	if (!token)
		exit(ERROR);
	j = 0;
	while (j < len)
	{
		if (info->token_lst->type == REDIRECT_LEFT_ONE || \
			info->token_lst->type == REDIRECT_RIGHT_ONE)
			token[j] = info->token_lst->token[j + *i + 1];
		else if (info->token_lst->type == REDIRECT_LEFT_TWO || \
			info->token_lst->type == REDIRECT_RIGHT_TWO)
			token[j] = info->token_lst->token[j + *i + 2];
		else
			token[j] = info->token_lst->token[j + *i];
		j++;
	}
	token[j] = '\0';
	lst_tmp = ft_lstnew_ms(token);
	if (info->token_lst->type == REDIRECT_LEFT_ONE)
		ft_lstinsert_ms(info, lst_tmp, i, REDIRECT_LEFT_ONE);
	else if (info->token_lst->type == REDIRECT_RIGHT_ONE)
		ft_lstinsert_ms(info, lst_tmp, i, REDIRECT_RIGHT_ONE);
	else if (info->token_lst->type == REDIRECT_LEFT_TWO)
		ft_lstinsert_ms(info, lst_tmp, i, REDIRECT_LEFT_TWO);
	else if (info->token_lst->type == REDIRECT_RIGHT_TWO)
		ft_lstinsert_ms(info, lst_tmp, i, REDIRECT_RIGHT_TWO);
	else
		ft_lstinsert_ms(info, lst_tmp, i, 42);
	set_token_type(token, info->token_lst->next);
}

int	split_token_for_redirect(t_info *info, size_t *i)
{
	size_t	len;

	len = ft_strlen(info->token_lst->token);
	if (info->token_lst->type >= REDIRECT_LEFT_ONE && \
		info->token_lst->type <= REDIRECT_RIGHT_TWO) // tokenの1文字目が「REDIRECT」のケース
	{
		if (len == 1)
			return (1);
		else if (len == 2 && \
			(ft_strncmp(info->token_lst->token, ">>", 2) == 0 || \
			ft_strncmp(info->token_lst->token, "<<", 2) == 0))
			return (1);
		else
			insert_split_token_for_redirect(info, i);
	}
	else // tokenの2文字目以降が「REDIRECT」のケース
		insert_split_token_for_redirect(info, i);
	return (1);
}
