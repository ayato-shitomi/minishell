/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 21:56:16 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	create_dl_lstnew(t_info *info, size_t *i)
{
	info->token_dl_lst = ft_dl_lstnew(info->split_command[*i]);
	info->token_dl_lst->dl_lst_first_flag = 1;
	info->token_dl_lst->dl_lst_last_flag = 1;
	set_token_type_dl(info->split_command[*i], info->token_dl_lst);
}

void	lexical_analysis(t_info *info)
{
	size_t			i;
	t_token_dl_lst	*dl_lst_tmp;

	info->split_command = ft_split_lex(info->parsed_command, ' ');
	if (!(info->split_command))
		exit(ERROR);
	free(info->parsed_command);
	i = 0;
	create_dl_lstnew(info, &i);
	i++;
	while (info->split_command[i])
	{
		dl_lst_tmp = ft_dl_lstnew(info->split_command[i]);
		ft_dl_lstadd_back(&(info->token_dl_lst), dl_lst_tmp);
		set_token_type_dl(info->split_command[i], \
			ft_dl_lstlast(info->token_dl_lst));
		i++;
	}
	free(info->split_command);
	lexical_analysis_2(info);
}
