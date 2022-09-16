/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/16 13:16:07 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	rtn_error_unclosed_quote(t_info *info, int flag)
{
	free(info->parsed_command);
	init_quote_flag(info);
	if (flag == 0)
		ft_putstr_fd("Fresh: syntax error near unexpected token `\"'\n", \
			STDERR_FILENO);
	else if (flag == 1)
		ft_putstr_fd("Fresh: syntax error near unexpected token `\''\n", \
			STDERR_FILENO);
	return (ERROR);
}

static void	space_check_and_set_char(char *command, t_info *info, \
	size_t i, size_t *j)
{
	if (info->is_in_dquote == 1 || info->is_in_squote == 1)
	{
		info->parsed_command[*j] = command[i];
		*j += 1;
		info->space_cnt = 0;
	}
	else if (command[i] != ' ' && \
		(info->is_in_dquote == 0 && info->is_in_squote == 0))
	{
		info->parsed_command[*j] = command[i];
		*j += 1;
		info->space_cnt = 0;
	}
	else
	{
		info->space_cnt++;
	}
	if (*j == 0 && info->space_cnt >= 1)
		return ;
	if (info->space_cnt == 1)
	{
		info->parsed_command[*j] = command[i];
		*j += 1;
	}
}

int	remove_space(char *command, t_info *info)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(command);
	info->parsed_command = (char *)ft_calloc(len + 1, sizeof(char));
	if (!info->parsed_command)
		exit(ERROR);
	while (command[i])
	{
		quote_check(command[i], info);
		space_check_and_set_char(command, info, i, &j);
		i++;
	}
	if (info->is_in_dquote)
		return (rtn_error_unclosed_quote(info, 0));
	else if (info->is_in_squote)
		return (rtn_error_unclosed_quote(info, 1));
	init_quote_flag(info);
	return (SUCCESS);
}
