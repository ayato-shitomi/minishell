#include "../includes/minishell.h"

static void	sig_int_handler_in_child_process(int signum)
{
	if (signum == SIGINT)
	{
		exit(ERROR);
		// write(STDOUT_FILENO, "\n", 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
}

void	set_sig_in_child_process(void)
{
	struct sigaction	sa_int;

	if (sigemptyset(&sa_int.sa_mask) == -1)
		exit(ERROR);
	sa_int.sa_flags = 0;
	if (sigaddset(&sa_int.sa_mask, SIGINT) == -1)
		exit(ERROR);
	sa_int.sa_handler = sig_int_handler_in_child_process;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		exit(ERROR);
}

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
		if (set_cmd_fd_and_exec(sentence_lst, environ, 0) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
