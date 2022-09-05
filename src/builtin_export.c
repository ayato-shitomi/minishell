#include "../includes/minishell.h"

static char	*get_base_key_in_the_rest(t_info *info, char *smallest_key, \
	char *base_key_in_the_rest)
{
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		if ((ft_strncmp(info->env_var_lst->key, smallest_key, \
			ft_strlen(info->env_var_lst->key)) > 0) && \
			(ft_strncmp(info->env_var_lst->key, base_key_in_the_rest, \
			ft_strlen(info->env_var_lst->key)) <= 0))
			base_key_in_the_rest = info->env_var_lst->key;
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (base_key_in_the_rest);
}

static char	*get_base_key_in_the_rest_first(t_info *info, \
	char *smallest_key)
{
	t_env_var_lst	*env_var_lst_tmp;
	char			*base_key_in_the_rest;

	env_var_lst_tmp = info->env_var_lst;
	base_key_in_the_rest = NULL;
	while (info->env_var_lst)
	{
		if (ft_strncmp(info->env_var_lst->key, smallest_key, \
			ft_strlen(info->env_var_lst->key)) > 0)
		{
			base_key_in_the_rest = info->env_var_lst->key;
			break ;
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (base_key_in_the_rest);
}

static char	*get_smallest_key(t_info *info)
{
	t_env_var_lst	*env_var_lst_tmp;
	char			*smallest_key;

	env_var_lst_tmp = info->env_var_lst;
	smallest_key = info->env_var_lst->key;
	info->env_var_lst = info->env_var_lst->next;
	while (info->env_var_lst)
	{
		if (ft_strncmp(info->env_var_lst->key, smallest_key, \
			ft_strlen(info->env_var_lst->key)) < 0)
			smallest_key = info->env_var_lst->key;
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (smallest_key);
}

static int	ft_export_case_no_arg(t_info *info)
{
	char			*smallest_key;
	char			*smallest_value;
	char			*base_key_in_the_rest;
	size_t			env_var_len;

	set_oldpwd(info);
	env_var_len = ft_env_var_lstsize(info->env_var_lst);
	if (env_var_len == 0)
		return (ERROR);
	printf("len = %zu\n", env_var_len); // デバッグ用
	smallest_key = get_smallest_key(info);
	smallest_value = get_env_value(info, smallest_key);
	ft_print_env(smallest_key, smallest_value, 1);
	env_var_len--;
	while (env_var_len)
	{
		if (env_var_len == 0)
			break ;
		base_key_in_the_rest = \
			get_base_key_in_the_rest_first(info, smallest_key);
		base_key_in_the_rest = get_base_key_in_the_rest(info, smallest_key, \
			base_key_in_the_rest);
		smallest_key = base_key_in_the_rest;
		smallest_value = get_env_value(info, smallest_key);
		ft_print_env(smallest_key, smallest_value, 1);
		env_var_len--;
	}
	return (SUCCESS);
}

int	ft_export(t_info *info)
{
	int				n;

	if (!info->sentence_lst->cmd_lst->next)
		n = ft_export_case_no_arg(info);
	else
	{
		n = validate_arg_at_ft_export(info);
		if (n != SUCCESS)
			return (n);
		n = ft_export_case_have_arg(info);
	}
	return (n);
}
