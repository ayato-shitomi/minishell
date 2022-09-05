#include "../includes/minishell.h"

static int	ft_cd_case_null(t_info *info)
{
	char			*pwd_value_tmp;
	char			*home_value;
	int				n;

	home_value = get_env_value(info, "HOME");
	if (!home_value)
		return (error_and_return("cd", NULL, "HOME not set"));
	if (!home_value[5])
		return (SUCCESS);
	n = chdir(home_value);
	if (n == 0)
	{
		pwd_value_tmp = get_env_value(info, "PWD");
		set_env_value(info, "OLDPWD", pwd_value_tmp);
		set_env_value(info, "PWD", home_value);
	}
	else
		n = error_and_return("cd", home_value, strerror(errno));
	return (n);
}

static char	*check_start_with_tilde(t_info *info, char *dest_dir, \
	size_t *delimiter_cnt_for_tilde)
{
	char	**split_dest_dir;
	char	*home_value;
	char	*dest_dir_tmp;
	size_t	i;

	if (!dest_dir)
		return (NULL);
	home_value = NULL;
	dest_dir_tmp = dest_dir;
	split_dest_dir = ft_split(dest_dir, '/');
	if (ft_strncmp(split_dest_dir[0], "~", ft_strlen(split_dest_dir[0])) == 0)
	{
		home_value = get_env_value(info, "HOME");
		i = 0;
		while (home_value[i])
		{
			if (home_value[i] == '/')
				*delimiter_cnt_for_tilde += 1;
			i++;
		}
		dest_dir_tmp = ft_strjoin(home_value, &dest_dir[1]);
		free(home_value);
	}
	ft_free_cmd(split_dest_dir);
	return (dest_dir_tmp);
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
	char			*dest_dir;
	int				n;
	size_t			delimiter_cnt_for_tilde;

	dest_dir = get_dest_dir(info);
	if (!dest_dir)
		n = ft_cd_case_null(info);
	else if (ft_strncmp(dest_dir, "/", 1) == 0)
		n = ft_cd_case_absolute_path(info, dest_dir);
	else
	{
		delimiter_cnt_for_tilde = 0;
		dest_dir = check_start_with_tilde(info, dest_dir, \
			&delimiter_cnt_for_tilde);
		n = ft_cd_case_multiple_relative_paths(info, dest_dir, \
			delimiter_cnt_for_tilde);
	}
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
