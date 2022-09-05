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
		if (ft_strncmp(info->env_var_lst->key, "OLDPWD\0", 7) == 0)
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
