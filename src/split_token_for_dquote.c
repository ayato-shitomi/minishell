/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_for_dquote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/16 20:44:59 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_token_for_dquote(t_info *info, char *token, size_t len, \
	size_t *i)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (info->token_dl_lst->type == EXPANDABLE_QUOTED)
			token[j] = info->token_dl_lst->token[j + *i + 1];
		else
			token[j] = info->token_dl_lst->token[j + *i];
		j++;
	}
	token[j] = '\0';
}

static size_t	get_len_for_dquote(t_info *info, size_t *i)
{
	if (info->token_dl_lst->type == EXPANDABLE_QUOTED)
		return (ft_strlen(info->token_dl_lst->token + *i + 1));
	else
		return (ft_strlen(info->token_dl_lst->token + *i));
}

static void	insert_split_token_for_dquote(t_info *info, size_t *i)
{
	size_t			len;
	t_token_dl_lst	*dl_lst_tmp;
	char			*token;

	len = get_len_for_dquote(info, i);
	token = (char *)ft_calloc(len + 1, sizeof(char));
	if (!token)
		exit(ERROR);
	set_token_for_dquote(info, token, len, i);
	dl_lst_tmp = ft_dl_lstnew(token);
	ft_dl_lstinsert(info, dl_lst_tmp, i, EXPANDABLE_QUOTED);
	set_token_type_dl(token, info->token_dl_lst->next);
	info->token_dl_lst->is_cat_with_next = 1;
}

static void	case_dquote_first(t_info *info, size_t *i)
{
	size_t	j;

	j = 0;
	while (info->token_dl_lst->token[*i])
	{
		if (*i != 0 && info->token_dl_lst->token[*i] == '\"')
		{
			if (!(info->token_dl_lst->token[*i + 1]))
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
			insert_split_token_for_dquote(info, i);
			return ;
		}
		*i += 1;
	}
}

int	split_token_for_dquote(t_info *info, size_t *i)
{
	if (info->token_dl_lst->type == EXPANDABLE_QUOTED)
		case_dquote_first(info, i);
	else
		insert_split_token_for_dquote(info, i);
	return (1);
}

/*
static void	case_dquote_first(t_info *info, size_t *i)
{
	size_t	j;

	j = 0;
	while (info->token_dl_lst->token[*i])
	{
		if (*i != 0 && info->token_dl_lst->token[*i] == '\"')
		{
			if (!(info->token_dl_lst->token[*i + 1])) 
			// case in the end of token is `"`
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
			insert_split_token_for_dquote(info, i); 
			// case in the end of token is NOT `"`
			return ;
		}
		*i += 1;
	}
}
*/

/*
int	split_token_for_dquote(t_info *info, size_t *i)
{
	if (info->token_dl_lst->type == EXPANDABLE_QUOTED) 
	// case in token's 1st char is `"`
		case_dquote_first(info, i);
	else // case in else is `"`
		insert_split_token_for_dquote(info, i);
	return (1);
}
*/
