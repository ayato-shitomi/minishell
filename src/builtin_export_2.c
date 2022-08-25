#include "../includes/minishell.h"

void	ft_print_env(char *key, char *value)
{
	if (value)
		printf("declare -x %s=\"%s\"\n", key, value);
	else
		printf("declare -x %s\n", key);
}

static int	set_i_for_insert(t_info *info, char *key, char *value, size_t *i)
{
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		if (ft_strncmp(key, info->env_var_lst->key, ft_strlen(key)) == 0)
		{
			if (info->env_var_lst->value)
				free(info->env_var_lst->value);
			info->env_var_lst->value = ft_strdup(value);
			info->env_var_lst = env_var_lst_tmp;
			return (1);
		}
		else if (ft_strncmp(key, info->env_var_lst->key, ft_strlen(key)) > 0)
			*i += 1;
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (SUCCESS);
}

static char	*get_key(t_info *info, char *value)
{
	char	*key;

	if (!value)
		key = ft_strdup(info->sentence_lst->cmd_lst->str);
	else
	{
		key = ft_strdup(info->sentence_lst->cmd_lst->str);
		key[ft_strlen(key) - ft_strlen(value) - 1] = '\0';
	}
	return (key);
}

void	ft_set_env(t_info *info, char *value)
{
	t_env_var_lst	*env_var_lst_tmp;
	t_env_var_lst	*env_lst_new;
	char			*key;
	size_t			i;
	size_t			j;

	env_var_lst_tmp = info->env_var_lst;
	key = get_key(info, value);
	i = 0;
	if (set_i_for_insert(info, key, value, &i) == 1)
		return ;
	j = 0;
	while (j < i)
	{
		info->env_var_lst = info->env_var_lst->next;
		j++;
	}
	env_lst_new = ft_env_var_lstnew(key, value);
	ft_env_var_lstinsert(info, env_lst_new, env_var_lst_tmp, i);
}

int	ft_export_case_have_arg(t_info *info)
{
	t_lst	*cmd_lst_tmp;
	char	*value;

	cmd_lst_tmp = info->sentence_lst->cmd_lst;
	info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
	while (info->sentence_lst->cmd_lst)
	{
		value = ft_strchr(info->sentence_lst->cmd_lst->str, '=');
		if (!value)
			ft_set_env(info, NULL);
		else
		{
			value += 1;
			if (!*value)
				ft_set_env(info, "");
			else
				ft_set_env(info, value);
		}
		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
	}
	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	return (SUCCESS);
}
