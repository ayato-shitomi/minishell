#include "../includes/minishell.h"

// static void	sig_int_handler_in_child_process(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		write(2, "check_2\n", 8);
// 		write(STDOUT_FILENO, "\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		exit(128 + signum);
// 	}
// }

// void	set_sig_in_child_process(t_info *info)
// {
// 	if (sigemptyset(&info->sa_int.sa_mask) == -1)
// 		exit(ERROR);
// 	info->sa_int.sa_flags = 0;
// 	if (sigaddset(&info->sa_int.sa_mask, SIGINT) == -1)
// 		exit(ERROR);
// 	info->sa_int.sa_handler = sig_int_handler_in_child_process;
// 	if (sigaction(SIGINT, &info->sa_int, NULL) == -1)
// 		exit(ERROR);
// }

voidset_sig_in_heredoc_parent()
{

}

static void	sig_int_handler_in_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "check\n", 6);
		g_exit_status = SIGINT;
		exit(ERROR);
	}
}

void	set_sig_in_heredoc(void)
{
	signal(SIGINT, sig_int_handler_in_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

static void	sig_int_handler_in_exec_cmd(int signum)
{
	write(2, "check_2\n", 8);
	if (signum == SIGINT)
		g_exit_status = SIGINT;
	else if (signum == SIGQUIT)
		g_exit_status = SIGQUIT;
}

void	set_sig_in_exec_cmd(void)
{
	signal(SIGINT, sig_int_handler_in_exec_cmd);
	signal(SIGQUIT, sig_int_handler_in_exec_cmd);
}

// void	set_sig_in_parent_process(t_info *info)
// {
// 	if (sigemptyset(&info->sa_int.sa_mask) == -1)
// 		exit(ERROR);
// 	info->sa_int.sa_flags = 0;
// 	if (sigaddset(&info->sa_int.sa_mask, SIGINT) == -1)
// 		exit(ERROR);
// 	info->sa_int.sa_handler = bb;
// 	// info->sa_int.sa_handler = SIG_IGN;
// 	if (sigaction(SIGINT, &info->sa_int, NULL) == -1)
// 		exit(ERROR);
// }

static void	sig_int_handler(int signum)
{
	write(2, "check_3\n", 8);
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
