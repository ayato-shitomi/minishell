/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:19:43 by mhida             #+#    #+#             */
/*   Updated: 2022/09/14 11:24:48 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	do_heredoc_parent_proc(int heredoc_pid, char *tmp_file, \
	int *status)
{
	pid_t	w_pid;

	set_sig_in_heredoc_parent();
	w_pid = waitpid(heredoc_pid, &*status, WUNTRACED);
	if (access(tmp_file, F_OK) == 0)
	{
		unlink(tmp_file);
		free(tmp_file);
	}
}

static void	do_heredoc_child_proc(t_info *info, int heredoc_pipe_fd[2], \
	int continue_flag, char *tmp_file)
{
	set_sig_in_heredoc_child();
	heredoc_child_process(info, heredoc_pipe_fd, \
		continue_flag, tmp_file);
}

static int	check_red_left_after_right_flag(t_info *info, \
	int heredoc_pipe_fd[2], int continue_flag)
{
	if (!info->red_left_after_right_flag)
	{
		if (init_and_set_fd_for_restore(info, 0) == ERROR)
			return (ERROR);
		if (set_pipe_fd_0(heredoc_pipe_fd) == ERROR)
			return (ERROR);
		if (continue_flag == 1)
			if (init_and_set_fd_for_restore(info, 2) == ERROR)
				return (ERROR);
	}
	else
		info->red_left_after_right_flag = 0;
	return (SUCCESS);
}

static int	check_exit_status_after_waitpid_in_heredoc(t_info *info, \
	int is_builtin_without_pipe)
{
	if (g_exit_status == SIGINT && !is_builtin_without_pipe)
	{
		init_and_set_fd_for_restore(info, 2);
		exit(ERROR);
	}
	else if (g_exit_status == SIGINT)
		return (42);
	return (SUCCESS);
}

int	heredoc(t_info *info, int is_builtin_without_pipe)
{
	int		continue_flag;
	int		heredoc_pipe_fd[2];
	int		heredoc_pid;
	char	*tmp_file;
	int		status;

	set_continue_flag(info->sentence_lst, &continue_flag);
	if (pipe_and_error_check(heredoc_pipe_fd) == ERROR)
		return (ERROR);
	make_tmp_file(&tmp_file);
	if (fork_and_error_check(&heredoc_pid) == ERROR)
		return (ERROR);
	else if (heredoc_pid == 0)
		do_heredoc_child_proc(info, heredoc_pipe_fd, continue_flag, tmp_file);
	else
	{
		do_heredoc_parent_proc(heredoc_pid, tmp_file, &status);
		if (check_exit_status_after_waitpid_in_heredoc(info, \
			is_builtin_without_pipe) == 42)
			return (42);
		if (check_red_left_after_right_flag(info, heredoc_pipe_fd, \
			continue_flag) == ERROR)
			return (ERROR);
	}
	return (WEXITSTATUS(status));
}
