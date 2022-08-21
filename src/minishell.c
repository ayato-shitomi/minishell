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

int	main(int ac, char **argv, char **envp)
{
	char	*command;
	t_info	info;

	if (ac != 1 || !argv)
		return (ERROR);
	header();
	info.envp = envp;
	// g_builtin_info.biip = &g_builtin_info;
	g_builtin_info.cwd = getcwd(NULL, 0);
	// g_builtin_info.biip->cwd = getcwd(NULL, 0);
	while (1)
	{
		printf("g_cwd = %s\n", g_builtin_info.cwd);
		// printf("g_biip_cwd = %s\n", g_builtin_info.biip->cwd);
		init_info(&info);
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
