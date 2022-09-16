/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_for_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:28 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_token_for_pipe(t_info *info, char *token, size_t len, \
	size_t *i)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (info->token_dl_lst->type == PIPE)
			token[j] = info->token_dl_lst->token[j + *i + 1];
		else
			token[j] = info->token_dl_lst->token[j + *i];
		j++;
	}
	token[j] = '\0';
}

static size_t	get_len_for_pipe(t_info *info, size_t *i)
{
	if (info->token_dl_lst->type == PIPE)
		return (ft_strlen(info->token_dl_lst->token + *i + 1));
	else
		return (ft_strlen(info->token_dl_lst->token + *i));
}

static void	insert_split_token_for_pipe(t_info *info, size_t *i)
{
	size_t			len;
	t_token_dl_lst	*dl_lst_tmp;
	char			*token;

	len = get_len_for_pipe(info, i);
	token = (char *)ft_calloc(len + 1, sizeof(char));
	if (!token)
		exit(ERROR);
	set_token_for_pipe(info, token, len, i);
	dl_lst_tmp = ft_dl_lstnew(token);
	ft_dl_lstinsert(info, dl_lst_tmp, i, PIPE);
	set_token_type_dl(token, info->token_dl_lst->next);
}

int	split_token_for_pipe(t_info *info, size_t *i)
{
	if (info->token_dl_lst->type == PIPE)
	{
		if (ft_strlen(info->token_dl_lst->token) == 1)
			return (1);
		insert_split_token_for_pipe(info, i);
	}
	else
		insert_split_token_for_pipe(info, i);
	return (1);
}

/*
int	split_token_for_pipe(t_info *info, size_t *i)
{
	if (info->token_dl_lst->type == PIPE) // case in token's 1st is `|`
	{
		if (ft_strlen(info->token_dl_lst->token) == 1)
			return (1);
		insert_split_token_for_pipe(info, i);
	}
	else // else token is `|`
		insert_split_token_for_pipe(info, i);
	return (1);
}
*/
