#include "../includes/minishell.h"

int	execute_command(t_info *info)
{
	int				status;
	t_sentence_lst	*sentence_lst_tmp;
	pid_t			pid;
	pid_t			w_pid;
	extern char		**environ;

	sentence_lst_tmp = info->sentence_lst;
	if (fork_and_error_check(&pid) == ERROR)
		return (ERROR);
	else if (pid == 0)
	{
		if (do_pipes(info->sentence_lst, 0, \
			ft_sentence_lstsize(info->sentence_lst), environ) == ERROR)
			return (ERROR);
	}
<<<<<<< HEAD
	w_pid = waitpid(pid, &status, WUNTRACED);
=======
	else
	{
		close(heredoc_pipe_fd[0]);
		w_pid = waitpid(pid, &status, WUNTRACED);
	}
	if (WEXITSTATUS(status) == 0)
		printf("\x1b[32m[+]\x1b[0m ");
	else
		printf("\x1b[31m[-]\x1b[0m ");
>>>>>>> 06640e6151f19e1f1fb2fe1a7a8b39f43dfec21f
	info->sentence_lst = sentence_lst_tmp;
	return (SUCCESS);
}
