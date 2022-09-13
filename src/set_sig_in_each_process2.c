/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sig_in_each_process2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:29:32 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:28 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	sig_handler_in_exec_builtin_without_pipe(int signum)
{
	if (signum == SIGINT)
		g_exit_status = SIGINT;
}

void	set_sig_in_exec_builtin_without_pipe(void)
{
	signal(SIGINT, sig_handler_in_exec_builtin_without_pipe);
	signal(SIGQUIT, SIG_IGN);
}

static void	sig_handler_in_exec_cmd_parent(int signum)
{
	if (signum == SIGINT)
		g_exit_status = SIGINT;
	else if (signum == SIGQUIT)
		g_exit_status = SIGQUIT;
}

void	set_sig_in_exec_cmd_parent(void)
{
	signal(SIGINT, sig_handler_in_exec_cmd_parent);
	signal(SIGQUIT, sig_handler_in_exec_cmd_parent);
}

void	set_sig_in_exec_cmd_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
