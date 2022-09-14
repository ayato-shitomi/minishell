/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 05:23:06 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd_and_lsts(t_info *info, char *command)
{
	free(command);
	ft_free_token_dl_lst(info);
	ft_free_sentence_lst(info);
}

void	free_env_var_lst(t_info *info)
{
	t_env_var_lst	*env_var_lst_tmp;

	while (info->env_var_lst)
	{
		env_var_lst_tmp = info->env_var_lst;
		if (info->env_var_lst->key)
			free(info->env_var_lst->key);
		if (info->env_var_lst->value)
			free(info->env_var_lst->value);
		info->env_var_lst = info->env_var_lst->next;
		free(env_var_lst_tmp);
	}
}
