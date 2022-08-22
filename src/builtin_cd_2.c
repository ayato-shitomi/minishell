#include "../includes/minishell.h"

int	ft_cd_case_absolute_path(t_info *info, char *dest_dir)
{
	int	n;
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	n = chdir(dest_dir);
	if (n == 0)
	{

	}
	else
		error_and_return("cd", dest_dir, strerror(errno));
	return (n);
}

int	ft_cd_case_relative_path(t_info *info, char *dest_dir)
{
	char			*pwd_value_tmp;
	int				n;
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	n = chdir(dest_dir);
	if (n == 0)
	{
		while (info->env_var_lst)
		{
			if (ft_strncmp(info->env_var_lst->key, "PWD", \
				ft_strlen(info->env_var_lst->key)) == 0)
			{
				pwd_value_tmp = ft_strdup(info->env_var_lst->value);
				if (info->env_var_lst->value)
					free(info->env_var_lst->value);
				info->env_var_lst->value = ft_strjoin_three(pwd_value_tmp, \
					"/", dest_dir);
				break ;
			}
			info->env_var_lst = info->env_var_lst->next;
		}
		info->env_var_lst = env_var_lst_tmp;
		while (info->env_var_lst)
		{
			if (ft_strncmp(info->env_var_lst->key, "OLDPWD", \
				ft_strlen(info->env_var_lst->key)) == 0)
			{
				if (info->env_var_lst->value)
					free(info->env_var_lst->value);
				info->env_var_lst->value = pwd_value_tmp;
				break ;
			}
			info->env_var_lst = info->env_var_lst->next;
		}
	}
	else
		error_and_return("cd", dest_dir, strerror(errno));
	info->env_var_lst = env_var_lst_tmp;
	return (n);
}

int	ft_cd_case_dot2(t_info *info)
{
	int	n;

	n = SUCCESS;
	if (!info)
		return (n);
	return (n);
}

int	ft_cd_case_dot1(t_info *info)
{
	char			*pwd_value;
	int				n;
	t_env_var_lst	*env_var_lst_tmp;

	n = SUCCESS;
	pwd_value = NULL;
	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		if (ft_strncmp(info->env_var_lst->key, "PWD", \
			ft_strlen(info->env_var_lst->key)) == 0)
		{
			pwd_value = ft_strdup(info->env_var_lst->value);
			n = chdir(info->env_var_lst->value);
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	while (info->env_var_lst)
	{
		if (ft_strncmp(info->env_var_lst->key, "OLDPWD", \
			ft_strlen(info->env_var_lst->key)) == 0)
		{
			if (info->env_var_lst->value)
				free(info->env_var_lst->value);
			info->env_var_lst->value = pwd_value;
			return (n);
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (n);
}
