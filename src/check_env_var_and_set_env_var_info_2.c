/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var_and_set_env_var_info_2.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/15 05:49:29 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_key_value_str_for_exit_status(
	t_lst *env_var_lst, int is_first_sentence)
{
	env_var_lst->key[0] = '?';
	env_var_lst->key[1] = '\0';
	if (is_first_sentence)
		env_var_lst->value = ft_strdup(ft_itoa(g_exit_status));
	else
		env_var_lst->value = ft_strdup("0");
	env_var_lst->str = (char *)ft_calloc(3, sizeof(char));
	if (!(env_var_lst->str))
		exit(ERROR);
	env_var_lst->str[0] = '$';
	env_var_lst->str[1] = '?';
	env_var_lst->str[2] = '\0';
}

void	set_exit_status_first(t_info *info, size_t *i, int is_first_sentence)
{
	t_lst	*env_var_lst;

	*i += 1;
	env_var_lst = ft_lstnew(NULL);
	set_lst_info(info, env_var_lst, ENV_VAR_LST);
	env_var_lst->key = (char *)ft_calloc(2, sizeof(char));
	if (!(env_var_lst->key))
		exit(ERROR);
	set_key_value_str_for_exit_status(env_var_lst, is_first_sentence);
	ft_lstadd_back(&(info->sentence_lst->env_var_lst), env_var_lst);
}
