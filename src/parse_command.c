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
		printf("type = %d\n", info->token_dl_lst->type);
		printf("first_flag = %d\n", info->token_dl_lst->dl_lst_first_flag);
		printf("last_flag = %d\n", info->token_dl_lst->dl_lst_last_flag);
		info->token_dl_lst = info->token_dl_lst->next;
		if (info->token_dl_lst->dl_lst_first_flag == 1)
			break ;
	}
	// ここまでデバッグ用
	if (syntax_analysis(info) == ERROR)
		return (ERROR);
	// ここからデバッグ用
	while (info->sentence_lst)
	{
		while (info->sentence_lst->cmd_lst)
		{
			printf("cmd_lst->str = %s\n", info->sentence_lst->cmd_lst->str);
			printf("cmd_lst->key = %s\n", info->sentence_lst->cmd_lst->key);
			printf("cmd_lst->value = %s\n", info->sentence_lst->cmd_lst->value);
			printf("cmd_lst->token_type = %d\n", info->sentence_lst->cmd_lst->token_type);
			printf("cmd_lst->lst_type = %d\n", info->sentence_lst->cmd_lst->lst_type);
			info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
		}
		while (info->sentence_lst->redirect_lst)
		{
			printf("redirect_lst->str = %s\n", info->sentence_lst->redirect_lst->str);
			printf("redirect_lst->key = %s\n", info->sentence_lst->redirect_lst->key);
			printf("redirect_lst->value = %s\n", info->sentence_lst->redirect_lst->value);
			printf("redirect_lst->token_type = %d\n", info->sentence_lst->redirect_lst->token_type);
			printf("redirect_lst->lst_type = %d\n", info->sentence_lst->redirect_lst->lst_type);
			info->sentence_lst->redirect_lst = info->sentence_lst->redirect_lst->next;
		}
		while (info->sentence_lst->env_var_lst)
		{
			printf("env_var_lst->str = %s\n", info->sentence_lst->env_var_lst->str);
			printf("env_var_lst->key = %s\n", info->sentence_lst->env_var_lst->key);
			printf("env_var_lst->value = %s\n", info->sentence_lst->env_var_lst->value);
			printf("env_var_lst->token_type = %d\n", info->sentence_lst->env_var_lst->token_type);
			printf("env_var_lst->lst_type = %d\n", info->sentence_lst->env_var_lst->lst_type);
			info->sentence_lst->env_var_lst = info->sentence_lst->env_var_lst->next;
		}
		info->sentence_lst = info->sentence_lst->next;
	}
	// ここまでデバッグ用
	// if (expansion(info) == ERROR)
	// 	return (ERROR);
	// if (execute_command(info) == ERROR)
	// 	return (ERROR);
	return (SUCCESS);
}
