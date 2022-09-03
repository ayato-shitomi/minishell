#include "../includes/minishell.h"

static void	exit_ctrl_d(void)
{
	printf("exit\n");
	exit(SUCCESS);
}

static void	remove_file(void)
{
	if (access("tmp.txt", F_OK) == 0)
		unlink("tmp.txt");
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

int	main(void)
{
	char	*command;
	t_info	info;

	header();
	info.exit_status = 0;
	init_env_var_lst(&info);
	while (1)
	{
		//printf("e_status = %d\n", info.exit_status);
		init_info(&info);
		init_sig(&info);
		command = readline(PROMPT);
		if (!command)
			exit_ctrl_d();
		else if (ft_strlen(command) > 0)
		{
			parse_command(command, &info);
				// exit(ERROR);
			add_history(command);
		}
		remove_file();
		free(command);
		ft_free_token_dl_lst(&info);
		ft_free_sentence_lst(&info);
	}
	free_env_var_lst(&info);
	return (SUCCESS);
}
