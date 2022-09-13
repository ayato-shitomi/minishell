/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:26 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:26 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_info *info)
{
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		ft_print_env(info->env_var_lst->key, info->env_var_lst->value, 0);
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (SUCCESS);
}
