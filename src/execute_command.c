#include "../includes/minishell.h"

int	execute_command(t_info *info)
{
	t_sentence_lst	*sentence_lst_tmp;
	pid_t			pid;
	pid_t			w_pid;
	int				status;
	int				heredoc_pipe_fd[2];

	sentence_lst_tmp = info->sentence_lst;
	if (pipe(heredoc_pipe_fd) == -1)
		exit(ERROR);
	pid = fork();
	if (pid < 0)
	{
		perror("bash");
		return (ERROR);
	}
	else if (pid == 0)
	{
		if (do_pipes(info->sentence_lst, 0, \
			ft_sentence_lstsize(info->sentence_lst)) == ERROR)
			return (ERROR);
	}
	else
	{
		close(heredoc_pipe_fd[0]);
		w_pid = waitpid(pid, &status, WUNTRACED);
	}
	if (WEXITSTATUS(status) == 0)
		printf("\x1b[32m[+]\x1b[0m ");
	else
		printf("\x1b[31m[-]\x1b[0m ");
	info->sentence_lst = sentence_lst_tmp;
	return (SUCCESS);
}
