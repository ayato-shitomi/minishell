#include "../includes/minishell.h"

int	parse_command(char *command, t_info *info)
{
	size_t	i; // デバッグ用

	i = 0; // デバッグ用
	if (remove_space(command, info) == ERROR)
		return (ERROR);
	// printf("parsed = %s\n", info->parsed_command);
	if (lexical_analysis(info) == ERROR)
		return (ERROR);
	// ここからデバッグ用
	while (1)
	{
		printf("token = %s\n", info->token_lst->token);
		printf("type = %d\n", info->token_lst->type);
		info->token_lst = info->token_lst->next;
		if (info->token_lst->lst_first_flag == 1)
			break ;
	}
	// ここまでデバッグ用
	if (syntax_analysis(info) == ERROR)
		return (ERROR);
	if (expansion(info) == ERROR)
		return (ERROR);
	if (execute_command(info) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
