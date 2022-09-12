#include "../includes/minishell.h"

static void	sig_handler_in_heredoc_parent(int signum)
{
	write(2, "check_9\n", 8);
	if (signum == SIGINT)
		g_exit_status = SIGINT;
	else if (signum == SIGQUIT)
		g_exit_status = SIGQUIT;
}

void	set_sig_in_heredoc_parent(t_info *info)
{
	if (!info)
		return ;
	signal(SIGINT, sig_handler_in_heredoc_parent);
	signal(SIGQUIT, SIG_IGN);
	// if (sigemptyset(&info->sa_int.sa_mask) == -1)
	// 	exit(ERROR);
	// if (sigemptyset(&info->sa_quit.sa_mask) == -1)
	// 	exit(ERROR);
	// info->sa_int.sa_flags = 0;
	// info->sa_quit.sa_flags = 0;
	// if (sigaddset(&info->sa_int.sa_mask, SIGINT) == -1)
	// 	exit(ERROR);
	// if (sigaddset(&info->sa_quit.sa_mask, SIGQUIT) == -1)
	// 	exit(ERROR);
	// info->sa_int.sa_handler = sig_handler_in_heredoc_parent;
	// info->sa_quit.sa_handler = SIG_IGN;
	// if (sigaction(SIGINT, &info->sa_int, NULL) == -1)
	// 	exit(ERROR);
	// if (sigaction(SIGQUIT, &info->sa_quit, NULL) == -1)
	// 	exit(ERROR);
}

static void	sig_int_handler_in_heredoc_child(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "check\n", 6);
		g_exit_status = SIGINT;
		exit(ERROR);
	}
}

void	set_sig_in_heredoc_child(void)
{
	signal(SIGINT, sig_int_handler_in_heredoc_child);
	signal(SIGQUIT, SIG_IGN);
}

static void	sig_handler_in_exec_builtin_without_pipe(int signum)
{
	write(2, "check_5\n", 8);
	if (signum == SIGINT)
		g_exit_status = SIGINT;
	else if (signum == SIGQUIT)
		g_exit_status = SIGQUIT;
}

void	set_sig_in_exec_builtin_without_pipe(void)
{
	signal(SIGINT, sig_handler_in_exec_builtin_without_pipe);
	signal(SIGQUIT, sig_handler_in_exec_builtin_without_pipe);
}

static void	sig_handler_in_exec_cmd_parent(int signum)
{
	write(2, "par_par\n", 8);
	if (signum == SIGINT)
		g_exit_status = SIGINT;
	else if (signum == SIGQUIT)
		g_exit_status = SIGQUIT;
}

// void	set_sig_in_exec_cmd_parent(t_info *info)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;

// 	if (!info)
// 		return ;
// 	// signal(SIGINT, sig_handler_in_exec_cmd_parent);
// 	// signal(SIGQUIT, SIG_IGN);
// 	if (sigemptyset(&sa_int.sa_mask) == -1)
// 		exit(ERROR);
// 	if (sigemptyset(&sa_quit.sa_mask) == -1)
// 		exit(ERROR);
// 	sa_int.sa_flags = 0;
// 	sa_quit.sa_flags = 0;
// 	if (sigaddset(&sa_int.sa_mask, SIGINT) == -1)
// 		exit(ERROR);
// 	if (sigaddset(&sa_quit.sa_mask, SIGQUIT) == -1)
// 		exit(ERROR);
// 	sa_int.sa_handler = sig_handler_in_exec_cmd_parent;
// 	sa_quit.sa_handler = SIG_IGN;
// 	if (sigaction(SIGINT, &sa_int, NULL) == -1)
// 		exit(ERROR);
// 	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
// 		exit(ERROR);
// }

void	set_sig_in_exec_cmd_parent(t_info *info)
{
	// struct sigaction	sa_int;
	// struct sigaction	sa_quit;

	// if (!info)
	// 	return ;
	// signal(SIGINT, sig_handler_in_exec_cmd_parent);
	// signal(SIGQUIT, SIG_IGN);
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
	info->sa_int.sa_handler = sig_handler_in_exec_cmd_parent;
	info->sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &info->sa_int, NULL) == -1)
		exit(ERROR);
	if (sigaction(SIGQUIT, &info->sa_quit, NULL) == -1)
		exit(ERROR);
}

// static void	sig_handler_in_exec_cmd_child(int signum)
// {
// 	write(2, "par_child\n", 10);
// 	if (signum == SIGINT)
// 		g_exit_status = SIGINT;
// 	else if (signum == SIGQUIT)
// 		g_exit_status = SIGQUIT;
// 	exit(ERROR);
// 	exit(128 + g_exit_status);
// }

void	set_sig_in_exec_cmd_child(t_info *info)
{
	// struct sigaction	sa_int;
	// struct sigaction	sa_quit;

	// signal(SIGINT, sig_handler_in_exec_cmd_parent);
	// signal(SIGQUIT, SIG_IGN);
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
	// sa_int.sa_handler = sig_handler_in_exec_cmd_child;
	// sa_quit.sa_handler = SIG_IGN;
	// if (sigaction(SIGINT, &sa_int, NULL) == -1)
	// 	exit(ERROR);
	// if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	// 	exit(ERROR);
}

// void	set_sig_in_exec_cmd_child(void)
// {
// 	signal(SIGINT, sig_handler_in_exec_cmd_child);
// 	signal(SIGQUIT, sig_handler_in_exec_cmd_child);
// }

// static void	sig_handler_in_exec_cmd(int signum)
// {
// 	write(2, "check_2\n", 8);
// 	if (signum == SIGINT)
// 		g_exit_status = SIGINT;
// 	else if (signum == SIGQUIT)
// 		g_exit_status = SIGQUIT;
// }

// void	set_sig_in_exec_cmd(void)
// {
// 	signal(SIGINT, sig_handler_in_exec_cmd);
// 	signal(SIGQUIT, sig_handler_in_exec_cmd);
// }

static void	sig_int_handler(int signum)
{
	write(2, "init\n", 5);
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
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (!info)
		return ;
	if (sigemptyset(&sa_int.sa_mask) == -1)
		exit(ERROR);
	if (sigemptyset(&sa_quit.sa_mask) == -1)
		exit(ERROR);
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	if (sigaddset(&sa_int.sa_mask, SIGINT) == -1)
		exit(ERROR);
	if (sigaddset(&sa_quit.sa_mask, SIGQUIT) == -1)
		exit(ERROR);
	sa_int.sa_handler = sig_int_handler;
	sa_quit.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		exit(ERROR);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		exit(ERROR);
}

// static void	sig_int_handler(int signum)
// {
// 	// write(2, "check_3\n", 8);
// 	if (signum == SIGINT)
// 	{
// 		g_exit_status = ERROR;
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	init_sig(t_info *info)
// {
// 	if (sigemptyset(&info->sa_int.sa_mask) == -1)
// 		exit(ERROR);
// 	if (sigemptyset(&info->sa_quit.sa_mask) == -1)
// 		exit(ERROR);
// 	info->sa_int.sa_flags = 0;
// 	info->sa_quit.sa_flags = 0;
// 	if (sigaddset(&info->sa_int.sa_mask, SIGINT) == -1)
// 		exit(ERROR);
// 	if (sigaddset(&info->sa_quit.sa_mask, SIGQUIT) == -1)
// 		exit(ERROR);
// 	info->sa_int.sa_handler = sig_int_handler;
// 	info->sa_quit.sa_handler = SIG_IGN;
// 	if (sigaction(SIGINT, &info->sa_int, NULL) == -1)
// 		exit(ERROR);
// 	if (sigaction(SIGQUIT, &info->sa_quit, NULL) == -1)
// 		exit(ERROR);
// }
