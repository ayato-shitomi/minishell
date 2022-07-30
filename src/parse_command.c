#include "../includes/minishell.h"

int	parse_command(char *command, t_info *info)
{
	if (!command)
		return (SUCCESS);
	if (remove_space(command, info) == ERROR)
		return (ERROR);
	// printf("space_removed = %s\n", info->parsed_command);
	if (lexical_analysis(info) == ERROR)
		return (ERROR);
	// ここからデバッグ用
	while (1)
	{
		printf("token = %s\n", info->token_dl_lst->token);
		// printf("type = %d\n", info->token_dl_lst->type);
		// printf("first_flag = %d\n", info->token_dl_lst->dl_lst_first_flag);
		printf("last_flag = %d\n", info->token_dl_lst->dl_lst_last_flag);
		info->token_dl_lst = info->token_dl_lst->next;
		if (info->token_dl_lst->dl_lst_first_flag == 1)
			break ;
	}
	// ここまでデバッグ用
	if (syntax_analysis(info) == ERROR)
		return (ERROR);
	// if (expansion(info) == ERROR)
	// 	return (ERROR);
	// if (execute_command(info) == ERROR)
	// 	return (ERROR);
	return (SUCCESS);
}
