/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:20:28 by mhida             #+#    #+#             */
/*   Updated: 2022/07/18 09:34:04 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	info->sentence_cnt = 0;
	info->token_cnt = 0;
	info->is_in_quote = 0;
	info->is_in_space = 0;
	// info->token_len = 0;
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
			//add_history(info.parsed_command);
			add_history(command);
		}
		// printf("line = %s\n", info.parsed_command);
		free(command);
		free(info.parsed_command);
		init_info(&info);
	}
	return (SUCCESS);
}
