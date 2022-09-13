/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:26 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:26 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_info *info)
{
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		if (ft_strcmp(info->env_var_lst->key, "PWD") == 0)
		{
			if (info->env_var_lst->value)
				printf("%s\n", info->env_var_lst->value);
			else
				printf("%s\n", getcwd(NULL, 0));
			info->env_var_lst = env_var_lst_tmp;
			return (SUCCESS);
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	printf("%s\n", getcwd(NULL, 0));
	info->env_var_lst = env_var_lst_tmp;
	return (SUCCESS);
}
