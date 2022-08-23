#include "../includes/minishell.h"

int	ft_pwd(t_info *info)
{
	t_env_var_lst	*env_var_lst_tmp;

	env_var_lst_tmp = info->env_var_lst;
	while (info->env_var_lst)
	{
		if (ft_strncmp(info->env_var_lst->key, "PWD", \
			ft_strlen(info->env_var_lst->key)) == 0)
		{
			printf("%s\n", info->env_var_lst->value);
			info->env_var_lst = env_var_lst_tmp;
			return (SUCCESS);
		}
		info->env_var_lst = info->env_var_lst->next;
	}
	info->env_var_lst = env_var_lst_tmp;
	return (ERROR);
}
