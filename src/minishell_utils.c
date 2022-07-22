/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:22:44 by mhida             #+#    #+#             */
/*   Updated: 2022/07/22 12:06:12 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_quote_flag(t_info *info)
{
	info->is_in_dquote = 0;
	info->is_in_squote = 0;
}

void	quote_check(char c, t_info *info) //旧is_quote
{
	if (c == '\"' && info->is_in_dquote == 0)
		info->is_in_dquote = 1;
	else if (c == '\"' && info->is_in_dquote == 1)
		info->is_in_dquote = 0;
	else if (c == '\'' && info->is_in_squote == 0)
		info->is_in_squote = 1;
	else if (c == '\'' && info->is_in_squote == 1)
		info->is_in_squote = 0;
}
