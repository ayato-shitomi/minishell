/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_by_redirect_lst_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:52:55 by mhida             #+#    #+#             */
/*   Updated: 2022/09/18 22:02:12 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_fd_out_flag_and_restore_fd_in_and_out(t_info *info)
{
	if (info->fd_out_restore_flag == 1)
	{
		info->fd_out_restore_flag = 0;
		if (init_and_set_fd_for_restore(info, 2) == ERROR)
			return (rtn_error());
		info->fd_out_restore_flag = 1;
	}
	else
	{
		info->fd_out_restore_flag = 0;
		if (init_and_set_fd_for_restore(info, 2) == ERROR)
			return (rtn_error());
	}
}

int	check_fd_in_flag_and_restore_fd_in_and_out(t_info *info)
{
	if (info->fd_in_restore_flag == 1)
	{
		info->fd_in_restore_flag = 0;
		if (init_and_set_fd_for_restore(info, 2) == ERROR)
			return (rtn_error());
		info->fd_in_restore_flag = 1;
	}
	else
	{
		info->fd_in_restore_flag = 0;
		if (init_and_set_fd_for_restore(info, 2) == ERROR)
			return (rtn_error());
	}
	return (SUCCESS);
}

static int	restore_fd_out(t_info *info)
{
	if (dup2(info->fd_for_restore_out, 1) == -1)
		return (ERROR);
	if (close(info->fd_for_restore_out) == -1)
		return (ERROR);
	info->fd_out_restore_flag = 0;
	return (SUCCESS);
}

static int	restore_fd_in(t_info *info)
{
	if (dup2(info->fd_for_restore_in, 0) == -1)
		return (ERROR);
	if (close(info->fd_for_restore_in) == -1)
		return (ERROR);
	info->fd_in_restore_flag = 0;
	return (SUCCESS);
}

int	init_and_set_fd_for_restore(t_info *info, int n)
{
	if (info->fd_in_restore_flag && n == 2)
		if (restore_fd_in(info) == ERROR)
			return (ERROR);
	if (info->fd_out_restore_flag && n == 2)
		if (restore_fd_out(info) == ERROR)
			return (ERROR);
	if (n == 0)
	{
		info->fd_for_restore_in = dup(n);
		if (info->fd_for_restore_in == -1)
			return (ERROR);
		info->fd_in_restore_flag = 1;
	}
	else if (n == 1)
	{
		info->fd_for_restore_out = dup(n);
		if (info->fd_for_restore_out == -1)
			return (ERROR);
		info->fd_out_restore_flag = 1;
	}
	return (SUCCESS);
}
