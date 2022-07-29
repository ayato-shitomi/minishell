#include "../includes/minishell.h"

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	exit(ERROR);
}

static void	init_sig(void)
{
	struct sigaction	sa;

	if (sigemptyset(&sa.sa_mask) == -1)
		exit(ERROR);
	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(ERROR);
}

static void	init_info(t_info *info)
{
	info->token_cnt = 0;
	info->is_in_dquote = 0;
	info->is_in_squote = 0;
	info->space_cnt = 0;
}

int	main(void)
{
	char	*command;
	t_info	info;

	header();
	init_info(&info);
	init_sig(); //signal系関数をセット
	while (1)
	{
		command = readline(PROMPT);
		if (command && ft_strlen(command) > 0)
		{
			if (parse_command(command, &info) == ERROR)
				exit(ERROR);
			add_history(command);
		}
		free(command);
		ft_free_token_lst(&info);
		// ft_free_split_command(info.split_command);
		init_info(&info);
	}
	return (SUCCESS);
}
