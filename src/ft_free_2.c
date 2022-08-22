#include "../includes/minishell.h"

void	free_env_var_lst(t_info *info)
{
	t_env_var_lst	*env_var_lst_tmp;

	while (info->env_var_lst)
	{
		env_var_lst_tmp = info->env_var_lst;
		if (info->env_var_lst->key)
			free(info->env_var_lst->key);
		if (info->env_var_lst->value)
			free(info->env_var_lst->value);
		info->env_var_lst = info->env_var_lst->next;
		free(env_var_lst_tmp);
	}
}
