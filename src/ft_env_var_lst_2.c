#include "../includes/minishell.h"

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
