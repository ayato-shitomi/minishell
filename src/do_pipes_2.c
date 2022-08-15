#include "../includes/minishell.h"

int	set_pipe_and_fork(int pipe_fd[2], pid_t *pid)
{
	if (pipe_and_error_check(pipe_fd) == ERROR)
		return (ERROR);
	if (fork_and_error_check(pid) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

t_sentence_lst	*set_sentence_lst_and_pipe_fd(t_sentence_lst *sentence_lst, \
	size_t cmd_cnt, int pipe_fd[2], size_t i)
{
	while (i++ < cmd_cnt - 1)
		sentence_lst = sentence_lst->next;
	set_pipe_fd_2(sentence_lst, pipe_fd);
	return (sentence_lst);
}

int	check_first_sentence(t_sentence_lst *sentence_lst, size_t i, \
	size_t cmd_cnt, char **environ)
{
	if (i == cmd_cnt - 1)
	{
		if (set_cmd_fd_and_exec(sentence_lst, environ) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
