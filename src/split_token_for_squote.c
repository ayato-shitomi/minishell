#include "../includes/minishell.h"

static void	insert_split_token_for_squote(t_info *info, size_t *i)
{
	size_t		j;
	size_t		len;
	t_token_lst	*lst_tmp;
	char		*token;

	if (info->token_lst->type == NOT_EXPANDABLE)
		len = ft_strlen(info->token_lst->token + *i + 1);
	else
		len = ft_strlen(info->token_lst->token + *i);
	token = (char *)ft_calloc(len + 1, sizeof(char));
	if (!token)
		exit(ERROR);
	j = 0;
	while (j < len)
	{
		if (info->token_lst->type == NOT_EXPANDABLE)
			token[j] = info->token_lst->token[j + *i + 1];
		else
			token[j] = info->token_lst->token[j + *i];
		j++;
	}
	token[j] = '\0';
	lst_tmp = ft_lstnew_ms(token);
	ft_lstinsert_ms(info, lst_tmp, i, NOT_EXPANDABLE);
	set_token_type(token, info->token_lst->next);
}

int	split_token_for_squote(t_info *info, size_t *i)
{
	size_t	j;
	size_t	i_start;

	i_start = *i;
	j = 0;
	if (info->token_lst->type == NOT_EXPANDABLE) // tokenの1文字目が「'」のケース
	{
		while (info->token_lst->token[*i])
		{
			if (*i != i_start && info->token_lst->token[*i] == '\'')
			{
				if (!(info->token_lst->token[*i + 1])) // tokenの最後の文字が「'」のケース
				{
					while (j < (*i - 1))
					{
						info->token_lst->token[j] = \
							info->token_lst->token[j + 1];
						j++;
					}
					info->token_lst->token[j] = '\0';
					return (1);
				}
				insert_split_token_for_squote(info, i); // tokenの最後の文字が「'」ではないケース
				return (1);
			}
			*i += 1;
		}
	}
	else // tokenの2文字目以降が「'」のケース
		insert_split_token_for_squote(info, i);
	return (1);
}
