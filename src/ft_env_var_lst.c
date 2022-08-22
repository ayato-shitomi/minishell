#include "../includes/minishell.h"

t_env_var_lst	*ft_env_var_lstlast(t_env_var_lst *env_var_lst)
{
	if (!env_var_lst)
		return (NULL);
	while (env_var_lst->next != NULL)
		env_var_lst = env_var_lst->next;
	return (env_var_lst);
}

void	ft_env_var_lstadd_back(t_env_var_lst **env_var_lst, \
	t_env_var_lst *new)
{
	t_env_var_lst	*env_var_lst_tmp;

	if (!new)
		return ;
	if (!(*env_var_lst))
	{
		*env_var_lst = new;
		return ;
	}
	else
	{
		env_var_lst_tmp = ft_env_var_lstlast(*env_var_lst);
		(ft_env_var_lstlast(*env_var_lst))->next = new;
		(ft_env_var_lstlast(*env_var_lst))->prev = env_var_lst_tmp;
	}
}

t_env_var_lst	*ft_env_var_lstnew(char *key, char *value)
{
	t_env_var_lst	*new_elem;

	new_elem = (t_env_var_lst *)ft_calloc(1, sizeof(t_env_var_lst));
	if (!new_elem)
		exit(ERROR);
	new_elem->key = ft_strdup(key);
	new_elem->value = ft_strdup(value);
	new_elem->prev = NULL;
	new_elem->next = NULL;
	return (new_elem);
}

static t_env_var_lst	*get_env_var_lst(char **environ, size_t i)
{
	char			*environ_tmp;
	char			*key_end_p;
	size_t			key_len;
	t_env_var_lst	*env_var_lst_tmp;

	environ_tmp = ft_strdup(environ[i]);
	key_end_p = ft_strchr(environ_tmp, '=');
	key_len = ft_strlen(environ_tmp) - ft_strlen(key_end_p);
	environ_tmp[key_len] = '\0';
	env_var_lst_tmp = ft_env_var_lstnew(environ_tmp, &environ[i][key_len + 1]);
	free(environ_tmp);
	return (env_var_lst_tmp);
}

void	init_env_var_lst(t_info *info)
{
	extern char		**environ;
	size_t			i;
	t_env_var_lst	*env_var_lst_tmp;

	info->env_var_lst = NULL;
	if (!environ)
		return ;
	if (!environ[0])
		return ;
	info->env_var_lst = get_env_var_lst(environ, 0);
	i = 1;
	while (environ[i])
	{
		env_var_lst_tmp = get_env_var_lst(environ, i);
		ft_env_var_lstadd_back(&(info->env_var_lst), env_var_lst_tmp);
		i++;
	}
}
