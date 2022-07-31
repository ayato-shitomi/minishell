#include "../includes/minishell.h"

static void	set_token_for_squote(t_info *info, char *token, size_t len, \
	size_t *i)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (info->token_dl_lst->type == NOT_EXPANDABLE)
			token[j] = info->token_dl_lst->token[j + *i + 1];
		else
			token[j] = info->token_dl_lst->token[j + *i];
		j++;
	}
	token[j] = '\0';
}

static size_t	get_len_for_squote(t_info *info, size_t *i)
{
	if (info->token_dl_lst->type == NOT_EXPANDABLE)
		return (ft_strlen(info->token_dl_lst->token + *i + 1));
	else
		return (ft_strlen(info->token_dl_lst->token + *i));
}

static void	insert_split_token_for_squote(t_info *info, size_t *i)
{
	size_t			len;
	t_token_dl_lst	*dl_lst_tmp;
	char			*token;

	len = get_len_for_squote(info, i);
	token = (char *)ft_calloc(len + 1, sizeof(char));
	if (!token)
		exit(ERROR);
	set_token_for_squote(info, token, len, i);
	dl_lst_tmp = ft_dl_lstnew(token);
	ft_dl_lstinsert(info, dl_lst_tmp, i, NOT_EXPANDABLE);
	set_token_type_dl(token, info->token_dl_lst->next);
}

static void	case_squote_first(t_info *info, size_t *i)
{
	size_t	j;

	j = 0;
	while (info->token_dl_lst->token[*i])
	{
		if (*i != 0 && info->token_dl_lst->token[*i] == '\'')
		{
			if (!(info->token_dl_lst->token[*i + 1])) // tokenの最後の文字が「'」のケース
			{
				while (j < (*i - 1))
				{
					info->token_dl_lst->token[j] = \
						info->token_dl_lst->token[j + 1];
					j++;
				}
				info->token_dl_lst->token[j] = '\0';
				return ;
			}
			insert_split_token_for_squote(info, i); // tokenの最後の文字が「'」ではないケース
			return ;
		}
		*i += 1;
	}
}

int	split_token_for_squote(t_info *info, size_t *i)
{
	if (info->token_dl_lst->type == NOT_EXPANDABLE) // tokenの1文字目が「'」のケース
		case_squote_first(info, i);
	else // tokenの2文字目以降が「'」のケース
		insert_split_token_for_squote(info, i);
	return (1);
}
