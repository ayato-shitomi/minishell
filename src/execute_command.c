#include "../includes/minishell.h"

void	put_exitstatus(int n)
{
	if (n != 0)
		printf("\x1b[31m[%d]\x1b[0m ", n);
	else
		printf("\x1b[32m[%d]\x1b[0m ", n);
}

int	execute_command(t_info *info)
{
	int				status;
	t_sentence_lst	*sentence_lst_tmp;
	pid_t			pid;
	pid_t			w_pid;

	sentence_lst_tmp = info->sentence_lst;
	if (fork_and_error_check(&pid) == ERROR)
		return (ERROR);
	else if (pid == 0)
	{
		set_sig_in_child_process(info);
		if (do_pipes(info, 0, \
			ft_sentence_lstsize(info->sentence_lst)) == ERROR)
			exit(ERROR);
	}
	else
	{
		set_sig_in_parent_process(info);
		w_pid = waitpid(pid, &status, WUNTRACED);
	}
	put_exitstatus(WEXITSTATUS(status));
	info->sentence_lst = sentence_lst_tmp;
	return (SUCCESS);
}
