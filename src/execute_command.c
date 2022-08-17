#include "../includes/minishell.h"

static void	printf_exit_status(int status)
{
	if (WEXITSTATUS(status) == 0)
		printf("\x1b[32m[+]\x1b[0m ");
	else
		printf("\x1b[31m[%d]\x1b[0m ", (WEXITSTATUS(status)));
}

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
		set_sig_in_child_process(info);
		if (do_pipes(info, 0, \
			ft_sentence_lstsize(info->sentence_lst), environ) == ERROR)
			return (ERROR);
	}
	else
	{
		set_sig_in_parent_process(info);
		w_pid = waitpid(pid, &status, WUNTRACED);
		printf_exit_status(status);
	}
	info->sentence_lst = sentence_lst_tmp;
	return (SUCCESS);
}
