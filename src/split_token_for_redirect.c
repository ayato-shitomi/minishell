/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_for_redirect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:28 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_dl_lst_type_and_dl_lstinsert(t_info *info, \
	t_token_dl_lst *dl_lst_tmp, size_t *i)
{
	if (info->token_dl_lst->type == REDIRECT_LEFT_ONE)
		ft_dl_lstinsert(info, dl_lst_tmp, i, REDIRECT_LEFT_ONE);
	else if (info->token_dl_lst->type == REDIRECT_RIGHT_ONE)
		ft_dl_lstinsert(info, dl_lst_tmp, i, REDIRECT_RIGHT_ONE);
	else if (info->token_dl_lst->type == REDIRECT_LEFT_TWO)
		ft_dl_lstinsert(info, dl_lst_tmp, i, REDIRECT_LEFT_TWO);
	else if (info->token_dl_lst->type == REDIRECT_RIGHT_TWO)
		ft_dl_lstinsert(info, dl_lst_tmp, i, REDIRECT_RIGHT_TWO);
	else
		ft_dl_lstinsert(info, dl_lst_tmp, i, 42);
}

static void	set_token_for_redirect(t_info *info, char *token, size_t *i, \
	size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (info->token_dl_lst->type == REDIRECT_LEFT_ONE || \
			info->token_dl_lst->type == REDIRECT_RIGHT_ONE)
			token[j] = info->token_dl_lst->token[j + *i + 1];
		else if (info->token_dl_lst->type == REDIRECT_LEFT_TWO || \
			info->token_dl_lst->type == REDIRECT_RIGHT_TWO)
			token[j] = info->token_dl_lst->token[j + *i + 2];
		else
			token[j] = info->token_dl_lst->token[j + *i];
		j++;
	}
	token[j] = '\0';
}

static size_t	get_len_for_redirect(t_info *info, size_t *i)
{
	if (info->token_dl_lst->type == REDIRECT_LEFT_ONE || \
		info->token_dl_lst->type == REDIRECT_RIGHT_ONE)
		return (ft_strlen(info->token_dl_lst->token + *i + 1));
	else if (info->token_dl_lst->type == REDIRECT_LEFT_TWO || \
		info->token_dl_lst->type == REDIRECT_RIGHT_TWO)
		return (ft_strlen(info->token_dl_lst->token + *i + 2));
	else
		return (ft_strlen(info->token_dl_lst->token + *i));
}

static void	insert_split_token_for_redirect(t_info *info, size_t *i)
{
	size_t			len;
	t_token_dl_lst	*dl_lst_tmp;
	char			*token;

	len = get_len_for_redirect(info, i);
	token = (char *)ft_calloc(len + 1, sizeof(char));
	if (!token)
		exit(ERROR);
	set_token_for_redirect(info, token, i, len);
	dl_lst_tmp = ft_dl_lstnew(token);
	check_dl_lst_type_and_dl_lstinsert(info, dl_lst_tmp, i);
	set_token_type_dl(token, info->token_dl_lst->next);
}

int	split_token_for_redirect(t_info *info, size_t *i)
{
	size_t	len;

	len = ft_strlen(info->token_dl_lst->token);
	if (info->token_dl_lst->type >= REDIRECT_LEFT_ONE && \
		info->token_dl_lst->type <= REDIRECT_RIGHT_TWO) // tokenの1文字目が「REDIRECT」のケース
	{
		if (len == 1)
			return (1);
		else if (len == 2 && \
			(ft_strncmp(info->token_dl_lst->token, ">>", 2) == 0 || \
			ft_strncmp(info->token_dl_lst->token, "<<", 2) == 0))
			return (1);
		else
			insert_split_token_for_redirect(info, i);
	}
	else // tokenの2文字目以降が「REDIRECT」のケース
		insert_split_token_for_redirect(info, i);
	return (1);
}
