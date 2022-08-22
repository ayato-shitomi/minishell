#include "../includes/minishell.h"

static int	ft_cd_case_tilde(t_info *info)
{
	char			*home_value;
	int				n;
	t_env_var_lst	*env_var_lst_tmp;

	n = SUCCESS;
	home_value = NULL;
	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		if (ft_strncmp(info->env_var_lst->key, "HOME", \
			ft_strlen(info->env_var_lst->key)) == 0)
			home_value = info->env_var_lst->value;
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	if (!home_value)
		home_value = getenv("HOME");
	if (!home_value[5])
		return (SUCCESS);
	while (info->env_var_lst)
	{
		if (ft_strncmp(info->env_var_lst->key, "PWD", \
			ft_strlen(info->env_var_lst->key)) == 0)
		{
			if (info->env_var_lst->value)
				free(info->env_var_lst->value);
			info->env_var_lst->value = ft_strdup(home_value);
			n = chdir(info->env_var_lst->value);
			break ;
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (n);
}

static int	ft_cd_case_null(t_info *info)
{
	char			*home_value;
	int				n;
	t_env_var_lst	*env_var_lst_tmp;

	n = SUCCESS;
	home_value = NULL;
	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		if (ft_strncmp(info->env_var_lst->key, "HOME", \
			ft_strlen(info->env_var_lst->key)) == 0)
			home_value = info->env_var_lst->value;
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	if (!home_value)
		return (error_and_return("cd", NULL, "HOME not set"));
	if (!home_value[5])
		return (SUCCESS);
	while (info->env_var_lst)
	{
		if (ft_strncmp(info->env_var_lst->key, "PWD", \
			ft_strlen(info->env_var_lst->key)) == 0)
		{
			if (info->env_var_lst->value)
				free(info->env_var_lst->value);
			info->env_var_lst->value = ft_strdup(home_value);
			n = chdir(info->env_var_lst->value);
			break ;
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (n);
}

static char	*get_dest_dir(t_info *info)
{
	if (info->sentence_lst->cmd_lst->next)
		return (info->sentence_lst->cmd_lst->next->str);
	else
		return (NULL);
}

int	ft_cd(t_info *info)
{
	char	*dest_dir;
	int		n;

	dest_dir = get_dest_dir(info);
	if (dest_dir == NULL)
		n = ft_cd_case_null(info);
	else if (ft_strncmp(dest_dir, "~", ft_strlen(dest_dir)) == 0)
		n = ft_cd_case_tilde(info);
	else if ((ft_strncmp(dest_dir, ".", ft_strlen(dest_dir)) == 0) || \
		(ft_strncmp(dest_dir, "./", ft_strlen(dest_dir)) == 0))
		n = ft_cd_case_dot1(info);
	else if ((ft_strncmp(dest_dir, "..", ft_strlen(dest_dir)) == 0) || \
		(ft_strncmp(dest_dir, "../", ft_strlen(dest_dir)) == 0))
		n = ft_cd_case_dot2(info);
	else if (ft_strncmp(dest_dir, "/", 1) == 0)
		n = ft_cd_case_absolute_path(info);
	else
		n = ft_cd_case_relative_path(info, dest_dir);
	return (n);
}

/*
int	main(void)
{
	char	*path = "/Users/ashitomi/Library";
	char	path_name[200];
	int		n;

	getcwd(path_name, 200);
	printf("before \t: %s\n", path_name);
	n = ft_cd(path);
	getcwd(path_name, 200);
	printf("after %d\t: %s\n", n, path_name);

	char	*not_ex_path = "/Unko/Unko/Unko";
	getcwd(path_name, 200);
	printf("before \t: %s\n", path_name);
	n = ft_cd(not_ex_path);
	getcwd(path_name, 200);
	printf("after %d\t: %s\n", n, path_name);

	char	*home = NULL;
	getcwd(path_name, 200);
	printf("before \t: %s\n", path_name);
	n = ft_cd(NULL);
	getcwd(path_name, 200);
	printf("after %d\t: %s\n", n, path_name);
	return (0);
}
*/
