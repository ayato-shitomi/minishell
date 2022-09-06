#include "../includes/minishell.h"

static void	ft_cd_case_multiple_relative_paths_2(t_info *info, char *dest_dir, \
	size_t delimiter_cnt_for_tilde)
{
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		// if (ft_strncmp(info->env_var_lst->key, "PWD", \
		// 	ft_strlen(info->env_var_lst->key)) == 0)
		if (ft_strcmp(info->env_var_lst->key, "PWD") == 0)
		{
			info->env_var_lst = env_var_lst_tmp;
			ft_cd_case_branch(info, dest_dir, delimiter_cnt_for_tilde);
			break ;
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
}

int	ft_cd_case_multiple_relative_paths(t_info *info, char *dest_dir, \
	size_t delimiter_cnt_for_tilde)
{
	char			*pwd_value_tmp;
	t_env_var_lst	*env_var_lst_tmp;
	int				n;

	env_var_lst_tmp = info->env_var_lst;
	n = chdir(dest_dir);
	if (n == 0)
	{
		pwd_value_tmp = get_env_value(info, "PWD");
		set_env_value(info, "OLDPWD", pwd_value_tmp);
		ft_cd_case_multiple_relative_paths_2(info, dest_dir, \
			delimiter_cnt_for_tilde);
	}
	else
		n = error_and_return("cd", dest_dir, strerror(errno));
	info->env_var_lst = env_var_lst_tmp;
	return (n);
}

int	ft_cd_case_absolute_path(t_info *info, char *dest_dir)
{
	char			*pwd_value_tmp;
	t_env_var_lst	*env_var_lst_tmp;
	int				n;
	size_t			i;

	env_var_lst_tmp = info->env_var_lst;
	i = 0;
	while (dest_dir[i] == '/')
	{
		if (dest_dir[i + 1] == '\0')
			dest_dir[1] = '\0';
		i++;
	}
	n = chdir(dest_dir);
	if (n == 0)
	{
		pwd_value_tmp = get_env_value(info, "PWD");
		set_env_value(info, "OLDPWD", pwd_value_tmp);
		set_env_value(info, "PWD", dest_dir);
	}
	else
		n = error_and_return("cd", dest_dir, strerror(errno));
	info->env_var_lst = env_var_lst_tmp;
	return (n);
}

void	set_env_value(t_info *info, char *env_key, char *env_value_for_set)
{
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		// if (ft_strncmp(info->env_var_lst->key, env_key, \
		// 	ft_strlen(info->env_var_lst->key)) == 0)
		if (ft_strcmp(info->env_var_lst->key, env_key) == 0)
		{
			if (info->env_var_lst->value)
				free(info->env_var_lst->value);
			info->env_var_lst->value = ft_strdup(env_value_for_set);
			break ;
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
}

char	*get_env_value(t_info *info, char *env_key)
{
	char			*env_value;
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	env_value = NULL;
	while (info->env_var_lst)
	{
		// if (ft_strncmp(info->env_var_lst->key, env_key, \
		// 	ft_strlen(info->env_var_lst->key)) == 0)
		if (ft_strcmp(info->env_var_lst->key, env_key) == 0)
			env_value = info->env_var_lst->value;
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (env_value);
}
