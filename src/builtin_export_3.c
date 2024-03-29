/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:26 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 13:32:00 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_oldpwd_2(t_info *info)
{
	t_env_var_lst	*env_var_lst_tmp;
	t_env_var_lst	*env_lst_new;
	char			*key;
	size_t			i;
	size_t			j;

	env_var_lst_tmp = info->env_var_lst;
	key = ft_strdup("OLDPWD");
	i = 0;
	if (set_i_for_insert(info, key, NULL, &i) == 1)
		return ;
	j = 0;
	while (j < i)
	{
		info->env_var_lst = info->env_var_lst->next;
		j++;
	}
	env_lst_new = ft_env_var_lstnew(key, NULL);
	ft_env_var_lstinsert(info, env_lst_new, env_var_lst_tmp, i);
}

void	set_oldpwd(t_info *info)
{
	t_env_var_lst	*env_var_lst_tmp;
	int				oldpwd_flag;

	env_var_lst_tmp = info->env_var_lst;
	oldpwd_flag = 0;
	while (info->env_var_lst)
	{
		if (ft_strcmp(info->env_var_lst->key, "OLDPWD") == 0)
		{
			oldpwd_flag = 1;
			break ;
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	if (!oldpwd_flag)
	{
		info->env_var_lst = env_var_lst_tmp;
		set_oldpwd_2(info);
	}
	info->env_var_lst = env_var_lst_tmp;
	return ;
}

char	*get_smallest_key(t_info *info)
{
	t_env_var_lst	*env_var_lst_tmp;
	char			*smallest_key;

	env_var_lst_tmp = info->env_var_lst;
	smallest_key = info->env_var_lst->key;
	info->env_var_lst = info->env_var_lst->next;
	while (info->env_var_lst)
	{
		if (ft_strcmp(info->env_var_lst->key, smallest_key) < 0)
			smallest_key = info->env_var_lst->key;
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (smallest_key);
}
