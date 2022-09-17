/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/18 00:28:20 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_ctrl_d(void)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(SUCCESS);
}

int	set_exit_status(int exit_status)
{
	g_exit_status = exit_status;
	return (exit_status);
}

// int	set_exit_status(t_info *info, int exit_status)
// {
// 	g_exit_status = exit_status;
// 	return (exit_status);
// 	// info->exit_status = exit_status;
// 	// return (exit_status);
// }
