#include "../includes/minishell.h"

void	set_continue_flag(t_sentence_lst *sentence_lst, int *continue_flag)
{
	*continue_flag = 0;
	if (sentence_lst->redirect_lst->next)
	{
		if (sentence_lst->redirect_lst->next->token_type == \
				REDIRECT_LEFT_TWO || \
			sentence_lst->redirect_lst->next->token_type == \
				REDIRECT_LEFT_ONE)
			*continue_flag = 1;
	}
}

int	heredoc(t_info *info)
{
	int		continue_flag;
	int		heredoc_pipe_fd[2];
	int		heredoc_pid;
	pid_t	w_pid;
	int		status;
	int		n;
	char	*tmp_file;

	set_continue_flag(info->sentence_lst, &continue_flag);
	if (pipe_and_error_check(heredoc_pipe_fd) == ERROR)
		return (ERROR);
	n = 0;
	while (1)
	{
		tmp_file = ft_itoa(n);
		if (access(tmp_file, F_OK) != 0)
			break ;
		free(tmp_file);
		if (n == INT_MAX)
			exit(ERROR);
		n++;
	}
	if (fork_and_error_check(&heredoc_pid) == ERROR)
		return (ERROR);
	else if (heredoc_pid == 0)
	{
		set_sig_in_heredoc(); // ①
		if (heredoc_child_process(info, heredoc_pipe_fd, \
			continue_flag, tmp_file) == ERROR)
			exit(ERROR);
		exit(ERROR);
	}
	else
	{
		w_pid = waitpid(heredoc_pid, &status, WUNTRACED);
		if (access(tmp_file, F_OK) == 0)
		{
			unlink(tmp_file);
			free(tmp_file);
		}
		if (g_exit_status == SIGINT) // ②
			exit(ERROR);
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
		// if (continue_flag == 1)
		// 	exit(SUCCESS);
	}
	return (WEXITSTATUS(status));
}

// int	heredoc(t_info *info) // 変更前
// {
// 	int		continue_flag;
// 	int		heredoc_pipe_fd[2];
// 	int		heredoc_pid;

// 	set_continue_flag(info->sentence_lst, &continue_flag);
// 	if (pipe_and_error_check(heredoc_pipe_fd) == ERROR)
// 		return (ERROR);
// 	if (fork_and_error_check(&heredoc_pid) == ERROR)
// 		return (ERROR);
// 	else if (heredoc_pid == 0)
// 	{
// 		init_and_set_fd_for_restore(info, 0);
// 		set_pipe_fd_0(heredoc_pipe_fd);
// 		if (continue_flag == 1)
// 			exit(SUCCESS);
// 	}
// 	else
// 	{
// 		if (heredoc_parent_process(info, heredoc_pipe_fd, \
// 			continue_flag) == ERROR)
// 			return (ERROR);
// 	}
// 	return (SUCCESS);
// }
