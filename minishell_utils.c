/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:22:44 by mhida             #+#    #+#             */
/*   Updated: 2022/07/18 09:22:46 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c, t_info *info)
{
	if (c == '\"' || c == '\'')
	{
		info->is_in_quote++;
		return (0);
	}
	return (1);
}

int	is_space(char c, t_info *info)
{
	if (c == ' ')
	{
		info->is_in_space++;
		return (0);
	}
	return (1);
}
