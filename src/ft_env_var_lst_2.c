#include "../includes/minishell.h"

static void	ft_env_var_lstinsert_2(t_info *info, t_env_var_lst *new, \
	t_env_var_lst *env_var_lst_tmp)
{
	info->env_var_lst = env_var_lst_tmp;
	info->env_var_lst = ft_env_var_lstlast(info->env_var_lst);
	info->env_var_lst->next = new;
	new->prev = info->env_var_lst;
	new->next = NULL;
	info->env_var_lst = env_var_lst_tmp;
}

void	ft_env_var_lstinsert(t_info *info, t_env_var_lst *new, \
	t_env_var_lst *env_var_lst_tmp, size_t i)
{
	if (!info->env_var_lst && i == 0)
		info->env_var_lst = new;
	else if (!info->env_var_lst)
		ft_env_var_lstinsert_2(info, new, env_var_lst_tmp);
	else if (i == 0)
	{
		new->prev = NULL;
		new->next = info->env_var_lst;
		info->env_var_lst->prev = new;
		info->env_var_lst = new;
	}
	else
	{
		new->prev = info->env_var_lst->prev;
		new->next = info->env_var_lst;
		info->env_var_lst->prev = new;
		new->prev->next = new;
		info->env_var_lst = env_var_lst_tmp;
	}
}

size_t	ft_env_var_lstsize(t_env_var_lst *env_var_lst)
{
	size_t	i;

	i = 0;
	if (!env_var_lst)
		return (0);
	while (env_var_lst)
	{
		env_var_lst = env_var_lst->next;
		i++;
	}
	return (i);
}
