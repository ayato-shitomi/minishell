#include "../includes/minishell.h"

static void	set_token_for_dquote(t_info *info, char *token, size_t len, \
	size_t *i)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (info->token_lst->type == EXPANDABLE_QUOTED)
			token[j] = info->token_lst->token[j + *i + 1];
		else
			token[j] = info->token_lst->token[j + *i];
		j++;
	}
	token[j] = '\0';
}

static size_t	get_len_for_dquote(t_info *info, size_t *i)
{
	if (info->token_lst->type == EXPANDABLE_QUOTED)
		return (ft_strlen(info->token_lst->token + *i + 1));
	else
		return (ft_strlen(info->token_lst->token + *i));
}

static void	insert_split_token_for_dquote(t_info *info, size_t *i)
{
	size_t		len;
	t_token_lst	*lst_tmp;
	char		*token;

	len = get_len_for_dquote(info, i);
	token = (char *)ft_calloc(len + 1, sizeof(char));
	if (!token)
		exit(ERROR);
	set_token_for_dquote(info, token, len, i);
	lst_tmp = ft_lstnew_ms(token);
	ft_lstinsert_ms(info, lst_tmp, i, EXPANDABLE_QUOTED);
	set_token_type(token, info->token_lst->next);
}

static void	case_dquote_first(t_info *info, size_t *i)
{
	size_t	j;

	j = 0;
	while (info->token_lst->token[*i])
	{
		if (*i != 0 && info->token_lst->token[*i] == '\"')
		{
			if (!(info->token_lst->token[*i + 1])) // tokenの最後の文字が「"」のケース
			{
				while (j < (*i - 1))
				{
					info->token_lst->token[j] = \
						info->token_lst->token[j + 1];
					j++;
				}
				info->token_lst->token[j] = '\0';
				return ;
			}
			insert_split_token_for_dquote(info, i); // tokenの最後の文字が「"」ではないケース
			return ;
		}
		*i += 1;
	}
}

int	split_token_for_dquote(t_info *info, size_t *i)
{
	if (info->token_lst->type == EXPANDABLE_QUOTED) // tokenの1文字目が「"」のケース
		case_dquote_first(info, i);
	else // tokenの2文字目以降が「"」のケース
		insert_split_token_for_dquote(info, i);
	return (1);
}
