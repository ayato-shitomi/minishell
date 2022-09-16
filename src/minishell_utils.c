/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/16 12:50:58 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fork_and_error_check(pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	return (SUCCESS);
}

int	pipe_and_error_check(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	return (SUCCESS);
}

void	set_lst_info(t_info *info, t_lst *lst, int flag)
{
	if (flag == REDIRECT_LST)
		lst->lst_type = REDIRECT_LST;
	else if (flag == CMD_LST)
		lst->lst_type = CMD_LST;
	else if (flag == ENV_VAR_LST)
		lst->lst_type = ENV_VAR_LST;
	if (flag == REDIRECT_LST || flag == CMD_LST)
		lst->token_type = info->token_dl_lst->type;
	else if (flag == ENV_VAR_LST)
		lst->token_type = info->token_dl_lst->type;
}

void	init_quote_flag(t_info *info)
{
	info->is_in_dquote = 0;
	info->is_in_squote = 0;
}

void	quote_check(char c, t_info *info)
{
	if (c == '\"' && info->is_in_dquote == 0 && info->is_in_squote == 0)
		info->is_in_dquote = 1;
	else if (c == '\"' && info->is_in_dquote == 1)
		info->is_in_dquote = 0;
	else if (c == '\'' && info->is_in_squote == 0 && info->is_in_dquote == 0)
		info->is_in_squote = 1;
	else if (c == '\'' && info->is_in_squote == 1)
		info->is_in_squote = 0;
}
