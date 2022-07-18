/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:20:54 by mhida             #+#    #+#             */
/*   Updated: 2022/07/18 09:20:57 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_analysis(char *command, t_info *info)
{
	//構文解析用関数
	if (!command && !info) //コンパイル時のunused対策
		return (ERROR);
	return (SUCCESS);
}

static int	lexical_analysis(char *command, t_info *info)
{
	//字句解析用関数
	size_t	i;

	i = 0;
	while (command[i])
	{
		if (is_quote(command[i], info) == 0)
		{
			//ダブルクォート、シングルクォートがある場合の処理
		}
		else if (is_space(command[i], info) == 0)
		{
			//トークン間に空白がある場合、もしくは入力値が空白のみの場合?の処理
		}
		// info->token_len++;
		i++;
	}
	return (SUCCESS);
}

int	parse_command(char *command, t_info *info)
{
	if (lexical_analysis(command, info) == ERROR)
		exit(ERROR);
	if (syntax_analysis(command, info) == ERROR)
		exit(ERROR);
	return (SUCCESS);
}
