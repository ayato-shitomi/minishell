/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:27 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
