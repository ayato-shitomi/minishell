#include "../includes/minishell.h"

int	set_pipe_and_fork(int pipe_fd[2], pid_t *pid)
{
	if (pipe_and_error_check(pipe_fd) == ERROR)
		return (ERROR);
	if (fork_and_error_check(pid) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	set_sentence_lst_and_pipe_fd(t_info *info, \
	size_t cmd_cnt, int pipe_fd[2], size_t i)
{
	while (i++ < cmd_cnt - 1)
		info->sentence_lst = info->sentence_lst->next;
	set_pipe_fd_2(info->sentence_lst, pipe_fd);
}

int	check_first_sentence(t_info *info, size_t i, \
	size_t cmd_cnt)
{
	if (i == cmd_cnt - 1)
	{
		if (set_cmd_fd_and_exec(info, 0) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
