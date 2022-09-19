/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:19:43 by mhida             #+#    #+#             */
/*   Updated: 2022/09/19 15:24:25 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	do_heredoc_parent_proc(t_info *info, int heredoc_pid, \
	char *tmp_file, int *status)
{
	pid_t	w_pid;

	init_and_set_fd_for_restore(info, 0);
	set_sig_in_heredoc_parent();
	w_pid = waitpid(heredoc_pid, &*status, WUNTRACED);
	if (access(tmp_file, F_OK) == 0)
	{
		unlink(tmp_file);
		free(tmp_file);
	}
}

static void	do_heredoc_child_proc(t_info *info, int heredoc_pipe_fd[2], \
	char *tmp_file)
{
	set_sig_in_heredoc_child();
	heredoc_child_process(info, heredoc_pipe_fd, tmp_file);
}

static int	restore_fd_in_heredoc_parent_proc(t_info *info, \
	int heredoc_pipe_fd[2], int continue_flag)
{
	if (set_pipe_fd_0(heredoc_pipe_fd) == ERROR)
		return (ERROR);
	if (continue_flag == 1 && \
	(info->sentence_lst->redirect_lst->next->token_type == REDIRECT_LEFT_ONE \
	|| info->sentence_lst->redirect_lst->next->token_type == REDIRECT_LEFT_TWO))
	{
		if (check_fd_out_flag_and_restore_fd_in_and_out(info) == ERROR)
			return (ERROR);
	}
	else if (continue_flag == 1 && \
	(info->sentence_lst->redirect_lst->next->token_type == REDIRECT_RIGHT_ONE \
	|| info->sentence_lst->redirect_lst->next->token_type \
	== REDIRECT_RIGHT_TWO))
	{
		info->fd_in_restore_flag = 0;
		if (init_and_set_fd_for_restore(info, 2) == ERROR)
			return (rtn_error());
		info->fd_in_restore_flag = 1;
	}
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
		do_heredoc_child_proc(info, heredoc_pipe_fd, tmp_file);
	else
	{
		do_heredoc_parent_proc(info, heredoc_pid, tmp_file, &status);
		if (check_exit_status_after_waitpid_in_heredoc(info, \
			is_builtin_without_pipe) == 42)
			return (42);
		if (restore_fd_in_heredoc_parent_proc(info, heredoc_pipe_fd, \
			continue_flag) == ERROR)
			return (ERROR);
	}
	return (WEXITSTATUS(status));
}
