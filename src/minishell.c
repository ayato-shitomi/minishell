#include "../includes/minishell.h"

static void	exit_ctrl_d(void)
{
	printf("exit\n");
	exit(SUCCESS);
}

static void	sig_int_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	init_sig(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

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

static void	init_info(t_info *info)
{
	info->is_in_dquote = 0;
	info->is_in_squote = 0;
	info->space_cnt = 0;
	info->token_dl_lst = NULL;
	info->parsed_command = NULL;
	info->split_command = NULL;
	info->sentence_lst = NULL;
}

/*
void	print_exit_status(void)
{
	char	*exit_status;

	exit_status = getenv('?');
	if (exit_status != NULL) {
		printf("%s", exit_status);
	}
	return ;
}
*/

int	main(void)
{
	char	*command;
	t_info	info;

	header();
	while (1)
	{
		init_info(&info);
		init_sig();
		command = readline(PROMPT);
		if (!command)
			exit_ctrl_d();
		else if (ft_strlen(command) > 0)
		{
			if (parse_command(command, &info) == ERROR)
				exit(ERROR);
			add_history(command);
		}
		free(command);
		ft_free_token_dl_lst(&info);
		ft_free_sentence_lst(&info);
	}
	return (SUCCESS);
}
