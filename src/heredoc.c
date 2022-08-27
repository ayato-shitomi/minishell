#include "../includes/minishell.h"

static void	set_continue_flag(t_sentence_lst *sentence_lst, int *continue_flag)
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

	set_continue_flag(info->sentence_lst, &continue_flag);
	if (pipe_and_error_check(heredoc_pipe_fd) == ERROR)
		return (ERROR);
	if (fork_and_error_check(&heredoc_pid) == ERROR)
		return (ERROR);
	else if (heredoc_pid == 0)
	{
		init_and_set_fd_for_restore(info, 0);
		set_pipe_fd_0(heredoc_pipe_fd);
		if (continue_flag == 1)
			exit(SUCCESS);
	}
	else
	{
		if (heredoc_parent_process(info, heredoc_pipe_fd, \
			continue_flag) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
