#include "../includes/minishell.h"

int	parse_command(char *command, t_info *info)
{
	// ここからデバッグ用変数
	// t_sentence_lst	*sentence_lst_tmp;
	// t_lst	*cmd_lst_tmp;
	// t_lst	*redirect_lst_tmp;
	// t_lst	*env_var_lst_tmp;
	// ここまでデバッグ用変数

	if (!command)
		return (SUCCESS);
	remove_space(command, info);
	if (ft_strlen(info->parsed_command) == 0)
		return (SUCCESS);
	lexical_analysis(info);
	// ここからデバッグ用
	// while (1)
	// {
	// 	printf("token = %s\n", info->token_dl_lst->token);
	// 	printf("type = %d\n", info->token_dl_lst->type);
	// 	printf("first_flag = %d\n", info->token_dl_lst->dl_lst_first_flag);
	// 	printf("last_flag = %d\n", info->token_dl_lst->dl_lst_last_flag);
	// 	printf("is_cat_with_next = %d\n", info->token_dl_lst->is_cat_with_next);
	// 	info->token_dl_lst = info->token_dl_lst->next;
	// 	if (info->token_dl_lst->dl_lst_first_flag == 1)
	// 		break ;
	// }
	// ここまでデバッグ用
	syntax_analysis(info);
	if (check_syntax_error(info) == ERROR)
		return (ERROR);
	expand_env_var(info);
	// ここからデバッグ用
	// sentence_lst_tmp = info->sentence_lst;
	// while (info->sentence_lst)
	// {
	// 	cmd_lst_tmp = info->sentence_lst->cmd_lst;
	// 	while (info->sentence_lst->cmd_lst)
	// 	{
	// 		printf("cmd_lst->str = %s\n", info->sentence_lst->cmd_lst->str);
	// 		printf("cmd_lst->key = %s\n", info->sentence_lst->cmd_lst->key);
	// 		printf("cmd_lst->value = %s\n", info->sentence_lst->cmd_lst->value);
	// 		printf("cmd_lst->token_type = %d\n", info->sentence_lst->cmd_lst->token_type);
	// 		printf("cmd_lst->lst_type = %d\n", info->sentence_lst->cmd_lst->lst_type);
	// 		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
	// 	}
	// 	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	// 	redirect_lst_tmp = info->sentence_lst->redirect_lst;
	// 	while (info->sentence_lst->redirect_lst)
	// 	{
	// 		printf("redirect_lst->str = %s\n", info->sentence_lst->redirect_lst->str);
	// 		printf("redirect_lst->key = %s\n", info->sentence_lst->redirect_lst->key);
	// 		printf("redirect_lst->value = %s\n", info->sentence_lst->redirect_lst->value);
	// 		printf("redirect_lst->token_type = %d\n", info->sentence_lst->redirect_lst->token_type);
	// 		printf("redirect_lst->lst_type = %d\n", info->sentence_lst->redirect_lst->lst_type);
	// 		info->sentence_lst->redirect_lst = info->sentence_lst->redirect_lst->next;
	// 	}
	// 	info->sentence_lst->redirect_lst = redirect_lst_tmp;
	// 	env_var_lst_tmp = info->sentence_lst->env_var_lst;
	// 	while (info->sentence_lst->env_var_lst)
	// 	{
	// 		printf("env_var_lst->str = %s\n", info->sentence_lst->env_var_lst->str);
	// 		printf("env_var_lst->key = %s\n", info->sentence_lst->env_var_lst->key);
	// 		printf("env_var_lst->value = %s\n", info->sentence_lst->env_var_lst->value);
	// 		printf("env_var_lst->token_type = %d\n", info->sentence_lst->env_var_lst->token_type);
	// 		printf("env_var_lst->lst_type = %d\n", info->sentence_lst->env_var_lst->lst_type);
	// 		info->sentence_lst->env_var_lst = info->sentence_lst->env_var_lst->next;
	// 	}
	// 	info->sentence_lst->env_var_lst = env_var_lst_tmp;
	// 	info->sentence_lst = info->sentence_lst->next;
	// }
	// info->sentence_lst = sentence_lst_tmp;
	// ここまでデバッグ用
	if (execute_command(info) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
