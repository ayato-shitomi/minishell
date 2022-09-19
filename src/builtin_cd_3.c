/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:26 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/19 15:57:18 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd_case_each_relative_path(t_info *info, char *dest_dir)
{
	char	*pwd_value_tmp;
	char	*env_value;

	pwd_value_tmp = get_env_value(info, "PWD");
	env_value = ft_strjoin_three(pwd_value_tmp, "/", dest_dir);
	if (pwd_value_tmp)
		free(pwd_value_tmp);
	set_env_value(info, "PWD", env_value);
}

void	ft_cd_case_dot2(t_info *info)
{
	char	*pwd_value_tmp;
	size_t	len;

	pwd_value_tmp = get_env_value(info, "PWD");
	len = ft_strlen(pwd_value_tmp);
	while (pwd_value_tmp[len] != '/')
		len--;
	pwd_value_tmp[len] = '\0';
	set_env_value(info, "PWD", pwd_value_tmp);
}

void	ft_cd_case_dot1(t_info *info)
{
	char	*pwd_value_tmp;

	pwd_value_tmp = get_env_value(info, "PWD");
	set_env_value(info, "PWD", pwd_value_tmp);
}

void	ft_cd_case_tilde(t_info *info)
{
	char	*home_value;

	home_value = get_env_value(info, "HOME");
	if (!home_value)
		home_value = ft_strdup(getenv("HOME"));
	if (!home_value[5])
		return ;
	set_env_value(info, "PWD", home_value);
}

void	ft_cd_case_branch(t_info *info, char *dest_dir, \
	size_t delimiter_cnt_for_tilde)
{
	char	**split_dest_dir;
	size_t	i;

	split_dest_dir = ft_split(dest_dir, '/');
	i = 0;
	while (split_dest_dir[i])
	{
		if (i == 0 && ft_strncmp(dest_dir, "/", 1) == 0)
		{
			ft_cd_case_tilde(info);
			i += delimiter_cnt_for_tilde - 1;
		}
		else if ((ft_strcmp(split_dest_dir[i], ".") == 0) || \
			(ft_strcmp(split_dest_dir[i], "./") == 0))
			ft_cd_case_dot1(info);
		else if ((ft_strcmp(split_dest_dir[i], "..") == 0) || \
			(ft_strcmp(split_dest_dir[i], "../") == 0))
			ft_cd_case_dot2(info);
		else
			ft_cd_case_each_relative_path(info, split_dest_dir[i]);
		i++;
	}
	ft_free_cmd(split_dest_dir);
}
