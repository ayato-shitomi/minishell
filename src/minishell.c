#include "../includes/minishell.h"

t_builtin_info	g_builtin_info;

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

static void	init_info(t_info *info, char **envp)
{
	info->is_in_dquote = 0;
	info->is_in_squote = 0;
	info->space_cnt = 0;
	info->token_dl_lst = NULL;
	info->parsed_command = NULL;
	info->split_command = NULL;
	info->sentence_lst = NULL;
	info->envp = envp;
}

int	main(int ac, char **argv, char **envp)
{
	char	*command;
	t_info	info;

	if (ac != 1 || !argv)
		return (ERROR);
	header();
	g_builtin_info.dest_dir = NULL;
	printf("g = %s\n", g_builtin_info.dest_dir);
	while (1)
	{
		init_info(&info, envp);
		init_sig(&info);
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
		remove_file();
	}
	return (SUCCESS);
}
