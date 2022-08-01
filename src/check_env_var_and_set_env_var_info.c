#include "../includes/minishell.h"

static void	set_key_and_value(t_lst *lst, t_lst *env_var_lst, size_t len, \
	size_t *i)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		env_var_lst->key[j] = lst->str[*i];
		*i += 1;
		j++;
	}
	env_var_lst->key[j] = '\0';
	env_var_lst->value = getenv(env_var_lst->key);
}

static void	set_env_var_info(t_info *info, t_lst *lst, size_t *i)
{
	size_t	i_tmp;
	size_t	len;
	t_lst	*env_var_lst;

	len = 0;
	env_var_lst = ft_lstnew(NULL);
	set_lst_info(info, env_var_lst, ENV_VAR_LST);
	*i += 1;
	i_tmp = *i;
	while (lst->str[*i] != '\"' && lst->str[*i] != ' ' && \
		lst->str[*i] != '?' && lst->str[*i] != '\0')
	{
		len++;
		*i += 1;
	}
	*i = i_tmp;
	env_var_lst->key = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(env_var_lst->key))
		exit(ERROR);
	set_key_and_value(lst, env_var_lst, len, i);
	ft_lstadd_back(&(info->sentence_lst->env_var_lst), env_var_lst);
}

void	check_env_var_and_set_env_var_info(t_info *info, t_lst *lst)
{
	size_t	i;

	i = 0;
	if (lst->token_type == NOT_EXPANDABLE)
		return ;
	else
	{
		while (lst->str[i])
		{
			if (lst->str[i] == '$')
				set_env_var_info(info, lst, &i);
			i++;
		}
	}
}
