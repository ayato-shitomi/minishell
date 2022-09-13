#include "../includes/minishell.h"

static int	check_heredoc(t_info *info)
{
	t_sentence_lst	*sentence_lst_tmp;
	t_lst			*red_lst_tmp;

	sentence_lst_tmp = info->sentence_lst;
	while (info->sentence_lst)
	{
		red_lst_tmp = info->sentence_lst->redirect_lst;
		while (info->sentence_lst->redirect_lst)
		{
			if ((info->sentence_lst->redirect_lst->token_type != NOT_EXPANDABLE) && \
				(ft_strcmp(info->sentence_lst->redirect_lst->str, "<<") == 0))
				return (1);
			info->sentence_lst->redirect_lst = info->sentence_lst->redirect_lst->next;
		}
		info->sentence_lst->redirect_lst = red_lst_tmp;
		info->sentence_lst = info->sentence_lst->next;
	}
	info->sentence_lst = sentence_lst_tmp;
	return (0);
}

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
	int	n;

	set_sig_in_exec_builtin_without_pipe();
	n = set_fd_by_redirect_lst(info, 1);
	// if (set_fd_by_redirect_lst(info, 1) == ERROR)
	if (n == ERROR)
	{
		init_and_set_fd_for_restore(info, 2);
		put_exitstatus(ERROR);
		return (ERROR);
	}
	if (n == 42)
	{
		status = ERROR;
		init_and_set_fd_for_restore(info, 2);
		put_exitstatus(status);
		return (ERROR);
	}
	status = exec_builtin_without_pipe(info);
	if (g_exit_status == SIGINT)
	{
		if (check_heredoc(info) == 1)
			status = ERROR;
		else if (status == SIGINT)
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
	set_sig_in_exec_cmd_child();
	if (fork_and_error_check(&pid) == ERROR)
		return (set_exit_status(ERROR));
	else if (pid == 0)
		do_pipes(info, 0, ft_sentence_lstsize(info->sentence_lst));
	else
	{
		set_sig_in_exec_cmd_parent();
		w_pid = waitpid(pid, &status, WUNTRACED);
		if (g_exit_status == SIGINT)
		{
			if (check_heredoc(info) == 1)
				status = ERROR;
			else if (status == SIGINT)
				status = 128 + SIGINT;
			else
				status = WEXITSTATUS(status);
			printf("\n");
		}
		else if (g_exit_status == SIGQUIT)
		{
			if (status == SIGQUIT)
			{
				status = 128 + SIGQUIT;
				printf("Quit: 3\n");
			}
			else
				status = WEXITSTATUS(status);
		}
		else
			status = WEXITSTATUS(status);
		put_exitstatus(status);
	}
	info->sentence_lst = sentence_lst_tmp;
	return (SUCCESS);
}
