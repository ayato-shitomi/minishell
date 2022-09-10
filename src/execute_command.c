#include "../includes/minishell.h"

void	put_exitstatus(int n)
{
	if (n != 0)
		printf("\x1b[31m[%d]\x1b[0m ", n);
	else
		printf("\x1b[32m[%d]\x1b[0m ", n);
	g_exit_status = n;
}

static int	set_fd_and_exec_builtin_without_pipe(t_info *info)
{
	int	status;

	set_sig_in_exec_cmd();
	if (set_fd_by_redirect_lst(info) == ERROR)
	{
		put_exitstatus(ERROR);
		return (ERROR);
	}
	status = exec_builtin_without_pipe(info);
	// printf("status = %d\n", status);
	// printf("w_status = %d\n", WEXITSTATUS(status));
	if (g_exit_status == SIGINT)
	{
		if (status == SIGINT)
			status = 128 + SIGINT;
		printf("\n");
	}
	else if (g_exit_status == SIGQUIT)
	{
		if (status == SIGQUIT)
			status = 128 + SIGQUIT;
		printf("Quit: 3\n");
	}
	init_and_set_fd_for_restore(info, 2);
	put_exitstatus(status);
	return (status);
}

int	execute_command(t_info *info)
{
	int				status;
	t_sentence_lst	*sentence_lst_tmp;
	pid_t			pid;
	pid_t			w_pid;

	sentence_lst_tmp = info->sentence_lst;
	if (info->sentence_lst->cmd_lst)
	{
		if (check_builtin(&info->sentence_lst->cmd_lst->str) && \
			!(info->sentence_lst->next) && info->sentence_lst->cmd_lst)
		{
			status = set_fd_and_exec_builtin_without_pipe(info);
			return (SUCCESS);
		}
	}
	set_sig_in_exec_cmd();
	if (fork_and_error_check(&pid) == ERROR)
		return (set_exit_status(ERROR));
	else if (pid == 0)
	{
		// set_sig_in_child_process(info);
		do_pipes(info, 0, ft_sentence_lstsize(info->sentence_lst));
	}
	else
	{
		// set_sig_in_parent_process();
		w_pid = waitpid(pid, &status, WUNTRACED);
		// printf("status = %d\n", status);
		// printf("w_status = %d\n", WEXITSTATUS(status));
		// printf("g_status = %d\n", g_exit_status);
		if (g_exit_status == SIGINT)
		{
			if (status == SIGINT)
				status = 128 + SIGINT;
			else
				status = WEXITSTATUS(status);
			printf("\n");
		}
		else if (g_exit_status == SIGQUIT)
		{
			if (status == SIGQUIT)
				status = 128 + SIGQUIT;
			else
				status = WEXITSTATUS(status);
			printf("Quit: 3\n");
		}
		else
			status = WEXITSTATUS(status);
		put_exitstatus(status);
	}
	// put_exitstatus(info, WEXITSTATUS(status));
	info->sentence_lst = sentence_lst_tmp;
	return (SUCCESS);
}
