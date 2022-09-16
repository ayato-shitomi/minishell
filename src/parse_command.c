/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/16 13:00:19 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_command(char *command, t_info *info)
{
	if (!command)
		return (SUCCESS);
	if (remove_space(command, info) == ERROR)
		return (set_exit_status(E_STATUS_SYN_ERR));
	if (ft_strlen(info->parsed_command) == 0)
		return (SUCCESS);
	lexical_analysis(info);
	syntax_analysis(info);
	if (check_syntax_error(info) == ERROR)
		return (set_exit_status(E_STATUS_SYN_ERR));
	expand_env_var(info);
	if (execute_command(info) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

// int	parse_command(char *command, t_info *info)
// {
// 	// debug val start
// 	// t_sentence_lst	*sentence_lst_tmp;
// 	// t_lst	*cmd_lst_tmp;
// 	// t_lst	*redirect_lst_tmp;
// 	// t_lst	*env_var_lst_tmp;
// 	// debug val end
// 	if (!command)
// 		return (SUCCESS);
// 	remove_space(command, info);
// 	if (ft_strlen(info->parsed_command) == 0)
// 		return (SUCCESS);
// 	lexical_analysis(info);
// 	// debug start
// 	// while (1)
// 	// {
// 	// 	printf("token = %s\n", info->token_dl_lst->token);
// 	// 	printf("type = %d\n", info->token_dl_lst->type);
// 	// 	printf("first_flag = %d\n",
// 	//  info->token_dl_lst->dl_lst_first_flag);
// 	// 	printf("last_flag = %d\n",
// 	// info->token_dl_lst->dl_lst_last_flag);
// 	// 	printf("is_cat_with_next = %d\n",
// 	// info->token_dl_lst->is_cat_with_next);
// 	// 	info->token_dl_lst = info->token_dl_lst->next;
// 	// 	if (info->token_dl_lst->dl_lst_first_flag == 1)
// 	// 		break ;
// 	// }
// 	// debug end
// 	syntax_analysis(info);
// 	if (check_syntax_error(info) == ERROR)
// 		return (set_exit_status(E_STATUS_SYN_ERR));
// 	// debug start
// 	// sentence_lst_tmp = info->sentence_lst;
// 	// while (info->sentence_lst)
// 	// {
// 	// 	cmd_lst_tmp = info->sentence_lst->cmd_lst;
// 	// 	while (info->sentence_lst->cmd_lst)
// 	// 	{
// 	// 		printf("cmd_lst->str = %s\n",
// 	// info->sentence_lst->cmd_lst->str);
// 	// 		printf("cmd_lst->key = %s\n", info->sentence_lst->cmd_lst->key);
// 	// 		printf("cmd_lst->value = %s\n",
// 	// info->sentence_lst->cmd_lst->value);
// 	// 		printf("cmd_lst->token_type = %d\n",
// 	// info->sentence_lst->cmd_lst->token_type);
// 	// 		printf("cmd_lst->lst_type = %d\n",
// 	// info->sentence_lst->cmd_lst->lst_type);
// 	// 		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
// 	// 	}
// 	// 	info->sentence_lst->cmd_lst = cmd_lst_tmp;
// 	// 	redirect_lst_tmp = info->sentence_lst->redirect_lst;
// 	// 	while (info->sentence_lst->redirect_lst)
// 	// 	{
// 	// 		printf("redirect_lst->str = %s\n",
// 	// info->sentence_lst->redirect_lst->str);
// 	// 		printf("redirect_lst->key = %s\n",
// 	// info->sentence_lst->redirect_lst->key);
// 	// 		printf("redirect_lst->value = %s\n",
// 	// info->sentence_lst->redirect_lst->value);
// 	// 		printf("redirect_lst->token_type = %d\n",
// 	// info->sentence_lst->redirect_lst->token_type);
// 	// 		printf("redirect_lst->lst_type = %d\n",
// 	// info->sentence_lst->redirect_lst->lst_type);
// 	// 		info->sentence_lst->redirect_lst =
// 	// info->sentence_lst->redirect_lst->next;
// 	// 	}
// 	// 	info->sentence_lst->redirect_lst = redirect_lst_tmp;
// 	// 	env_var_lst_tmp = info->sentence_lst->env_var_lst;
// 	// 	while (info->sentence_lst->env_var_lst)
// 	// 	{
// 	// 		printf("env_var_lst->str = %s\n",
// 	// info->sentence_lst->env_var_lst->str);
// 	// 		printf("env_var_lst->key = %s\n",
// 	// info->sentence_lst->env_var_lst->key);
// 	// 		printf("env_var_lst->value = %s\n",
// 	// info->sentence_lst->env_var_lst->value);
// 	// 		printf("env_var_lst->token_type = %d\n",
// 	// info->sentence_lst->env_var_lst->token_type);
// 	// 		printf("env_var_lst->lst_type = %d\n",
// 	// info->sentence_lst->env_var_lst->lst_type);
// 	// 		info->sentence_lst->env_var_lst =
// 	// info->sentence_lst->env_var_lst->next;
// 	// 	}
// 	// 	info->sentence_lst->env_var_lst = env_var_lst_tmp;
// 	// 	info->sentence_lst = info->sentence_lst->next;
// 	// }
// 	// info->sentence_lst = sentence_lst_tmp;
// 	// debug end
// 	expand_env_var(info);
// 	// debug start
// 	// sentence_lst_tmp = info->sentence_lst;
// 	// while (info->sentence_lst)
// 	// {
// 	// 	cmd_lst_tmp = info->sentence_lst->cmd_lst;
// 	// 	while (info->sentence_lst->cmd_lst)
// 	// 	{
// 	// 		printf("cmd_lst->str = %s\n",
// 	// info->sentence_lst->cmd_lst->str);
// 	// 		printf("cmd_lst->key = %s\n",
// 	// info->sentence_lst->cmd_lst->key);
// 	// 		printf("cmd_lst->value = %s\n",
// 	// info->sentence_lst->cmd_lst->value);
// 	// 		printf("cmd_lst->token_type = %d\n",
// 	// info->sentence_lst->cmd_lst->token_type);
// 	// 		printf("cmd_lst->lst_type = %d\n",
// 	// info->sentence_lst->cmd_lst->lst_type);
// 	// 		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
// 	// 	}
// 	// 	info->sentence_lst->cmd_lst = cmd_lst_tmp;
// 	// 	redirect_lst_tmp = info->sentence_lst->redirect_lst;
// 	// 	while (info->sentence_lst->redirect_lst)
// 	// 	{
// 	// 		printf("redirect_lst->str = %s\n",
// 	// info->sentence_lst->redirect_lst->str);
// 	// 		printf("redirect_lst->key = %s\n",
// 	// info->sentence_lst->redirect_lst->key);
// 	// 		printf("redirect_lst->value = %s\n",
// 	// info->sentence_lst->redirect_lst->value);
// 	// 		printf("redirect_lst->token_type = %d\n",
// 	// info->sentence_lst->redirect_lst->token_type);
// 	// 		printf("redirect_lst->lst_type = %d\n",
// 	// info->sentence_lst->redirect_lst->lst_type);
// 	// 		info->sentence_lst->redirect_lst =
// 	// info->sentence_lst->redirect_lst->next;
// 	// 	}
// 	// 	info->sentence_lst->redirect_lst = redirect_lst_tmp;
// 	// 	env_var_lst_tmp = info->sentence_lst->env_var_lst;
// 	// 	while (info->sentence_lst->env_var_lst)
// 	// 	{
// 	// 		printf("env_var_lst->str = %s\n",
// 	// info->sentence_lst->env_var_lst->str);
// 	// 		printf("env_var_lst->key = %s\n",
// 	// info->sentence_lst->env_var_lst->key);
// 	// 		printf("env_var_lst->value = %s\n",
// 	// info->sentence_lst->env_var_lst->value);
// 	// 		printf("env_var_lst->token_type = %d\n",
// 	// info->sentence_lst->env_var_lst->token_type);
// 	// 		printf("env_var_lst->lst_type = %d\n",
// 	// info->sentence_lst->env_var_lst->lst_type);
// 	// 		info->sentence_lst->env_var_lst =
// 	// info->sentence_lst->env_var_lst->next;
// 	// 	}
// 	// 	info->sentence_lst->env_var_lst = env_var_lst_tmp;
// 	// 	info->sentence_lst = info->sentence_lst->next;
// 	// }
// 	// info->sentence_lst = sentence_lst_tmp;
// 	// debug end
// 	if (execute_command(info) == ERROR)
// 		return (ERROR);
// 	return (SUCCESS);
// }
