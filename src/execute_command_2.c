/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 07:48:36 by mhida             #+#    #+#             */
/*   Updated: 2022/09/14 10:55:44 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_builtin_without_pipe_after_set_redirect(t_info *info, int n)
{
	int	status;

	if (n == ERROR)
	{
		init_and_set_fd_for_restore(info, 2);
		put_exitstatus(ERROR);
		return (ERROR);
	}
	if (n == 42)
	{
		status = ERROR;
		init_and_set_fd_for_restore(info, 2);
		put_exitstatus(status);
		return (ERROR);
	}
	return (SUCCESS);
}

int	set_exit_status_after_waitpid_in_exec_cmd(t_info *info, int status)
{
	if (g_exit_status == SIGINT)
	{
		if (check_heredoc(info) == 1)
			status = ERROR;
		else if (status == SIGINT)
			status = 128 + SIGINT;
		else
			status = WEXITSTATUS(status);
		printf("\n");
	}
	else if (g_exit_status == SIGQUIT)
	{
		if (status == SIGQUIT)
		{
			status = 128 + SIGQUIT;
			printf("Quit: 3\n");
		}
		else
			status = WEXITSTATUS(status);
	}
	else
		status = WEXITSTATUS(status);
	return (status);
}

int	check_builtin_without_pipe(t_info *info)
{
	if (check_builtin(&info->sentence_lst->cmd_lst->str) && \
		!(info->sentence_lst->next) && info->sentence_lst->cmd_lst)
	{
		set_fd_and_exec_builtin_without_pipe(info);
		return (1);
	}
	return (0);
}
