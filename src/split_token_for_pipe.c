#include "../includes/minishell.h"

static void	insert_split_token_for_pipe(t_info *info, size_t *i)
{
	size_t		j;
	size_t		len;
	t_token_lst	*lst_tmp;
	char		*token;

	if (info->token_lst->type == PIPE)
		len = ft_strlen(info->token_lst->token + *i + 1);
	else
		len = ft_strlen(info->token_lst->token + *i);
	token = (char *)ft_calloc(len + 1, sizeof(char));
	if (!token)
		exit(ERROR);
	j = 0;
	while (j < len)
	{
		if (info->token_lst->type == PIPE)
			token[j] = info->token_lst->token[j + *i + 1];
		else
			token[j] = info->token_lst->token[j + *i];
		j++;
	}
	token[j] = '\0';
	lst_tmp = ft_lstnew_ms(token);
	ft_lstinsert_ms(info, lst_tmp, i, PIPE);
	set_token_type(token, info->token_lst->next);
}

int	split_token_for_pipe(t_info *info, size_t *i)
{
	if (info->token_lst->type == PIPE) // tokenの1文字目が「|」のケース
	{
		if (ft_strlen(info->token_lst->token) == 1)
			return (1);
		insert_split_token_for_pipe(info, i);
	}
	else // tokenの2文字目以降が「|」のケース
		insert_split_token_for_pipe(info, i);
	return (1);
}
