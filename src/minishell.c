/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 05:22:54 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_ctrl_d(void)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(SUCCESS);
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
	info->fd_in_restore_flag = 0;
	info->fd_out_restore_flag = 0;
	info->red_left_after_right_flag = 0;
}

int	main(int ac, char **argv, char **envp)
{
	char	*command;
	t_info	info;

	(void)ac;
	(void)argv;
	header();
	g_exit_status = 0;
	init_env_var_lst(&info, envp);
	while (1)
	{
		init_info(&info);
		init_sig(&info);
		command = readline(PROMPT);
		if (!command)
			exit_ctrl_d();
		else if (ft_strlen(command) > 0)
		{
			parse_command(command, &info);
			add_history(command);
		}
		free_cmd_and_lsts(&info, command);
	}
	free_env_var_lst(&info);
	return (SUCCESS);
}
