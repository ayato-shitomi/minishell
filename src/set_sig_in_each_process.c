#include "../includes/minishell.h"

static void	sig_handler_in_heredoc_parent(int signum)
{
	// write(2, "check_9\n", 8);
	if (signum == SIGINT)
		g_exit_status = SIGINT;
	else if (signum == SIGQUIT)
		g_exit_status = SIGQUIT;
}

void	set_sig_in_heredoc_parent(void)
{
	signal(SIGINT, sig_handler_in_heredoc_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	set_sig_in_heredoc_child(void)
{
	// signal(SIGINT, sig_int_handler_in_heredoc_child);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

static void	sig_handler_in_exec_builtin_without_pipe(int signum)
{
	// write(2, "check_5\n", 8);
	if (signum == SIGINT)
		g_exit_status = SIGINT;
	// else if (signum == SIGQUIT)
	// 	g_exit_status = SIGQUIT;
}

void	set_sig_in_exec_builtin_without_pipe(void)
{
	signal(SIGINT, sig_handler_in_exec_builtin_without_pipe);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGQUIT, sig_handler_in_exec_builtin_without_pipe);
}

static void	sig_handler_in_exec_cmd_parent(int signum)
{
	// write(2, "par_par\n", 8);
	if (signum == SIGINT)
		g_exit_status = SIGINT;
	else if (signum == SIGQUIT)
		g_exit_status = SIGQUIT;
}

void	set_sig_in_exec_cmd_parent(void)
{
	signal(SIGINT, sig_handler_in_exec_cmd_parent);
	signal(SIGQUIT, sig_handler_in_exec_cmd_parent);
}

void	set_sig_in_exec_cmd_child(void)
{
	// signal(SIGINT, sig_handler_in_exec_cmd_parent);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	// signal(SIGQUIT, SIG_IGN);
}

static void	sig_int_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = ERROR;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_sig(t_info *info)
{
	if (sigemptyset(&info->sa_int.sa_mask) == -1)
		exit(ERROR);
	if (sigemptyset(&info->sa_quit.sa_mask) == -1)
		exit(ERROR);
	info->sa_int.sa_flags = 0;
	info->sa_quit.sa_flags = 0;
	if (sigaddset(&info->sa_int.sa_mask, SIGINT) == -1)
		exit(ERROR);
	if (sigaddset(&info->sa_quit.sa_mask, SIGQUIT) == -1)
		exit(ERROR);
	info->sa_int.sa_handler = sig_int_handler;
	info->sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &info->sa_int, NULL) == -1)
		exit(ERROR);
	if (sigaction(SIGQUIT, &info->sa_quit, NULL) == -1)
		exit(ERROR);
}
