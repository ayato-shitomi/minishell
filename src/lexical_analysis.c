/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:52:22 by mhida             #+#    #+#             */
/*   Updated: 2022/07/22 12:55:10 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_token_type(char *token, t_info *info, size_t i)
{
	size_t	len;

	len = ft_strlen(token);
	if (ft_strncmp(token, "|", len) == 0)
		info->token_type[i] = 3;
	else if (ft_strncmp(token, ">", len) == 0 || \
		ft_strncmp(token, "<", len) == 0 || ft_strncmp(token, ">>", len) == 0 \
		ft_strncmp(token, "<<", len) == 0)
		info->token_type = 4;
	else
	{
		if (ft_strncmp(token, "\"", 1) == 0)
			info->token_type = 1;
		else if (ft_strncmp(token, "\'", 1) == 0)
			info->token_type = 2;
		else
			info->token_type = 0;
	}
}

static size_t	get_token_cnt(char **split_command)
{
	size_t	i;

	i = 0;
	while (split_command[i])
		i++;
	return (i);
}

int	lexical_analysis(char *command, t_info *info)
{
	//字句解析用関数
	size_t	i;

	if(!command)
		return (ERROR); //unused対策
	info->split_command = ft_split_ms(info->parsed_command, info);
	if (!(info->split_command))
	{
		//エラー処理書く
		return (ERROR);
	}
	info->token_cnt = get_token_cnt(info->split_command);
	info->token_type = (int *)ft_calloc(info->token_cnt, sizeof(int));
	if (!(info->token_type))
	{
		//エラー処理書く
		return (ERROR);
	}
	i = 0;
	while (info->split_command[i])
	{
		set_token_type(info->split_command[i], info, i);
		i++;
	}
	return (SUCCESS);
}
