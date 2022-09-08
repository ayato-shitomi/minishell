#include "../includes/minishell.h"

static void	set_key_value_str_for_exit_status(t_lst *env_var_lst)
{
	env_var_lst->key[0] = '?';
	env_var_lst->key[1] = '\0';
	env_var_lst->value = ft_strdup(ft_itoa(g_exit_status));
	env_var_lst->str = (char *)ft_calloc(3, sizeof(char));
	if (!(env_var_lst->str))
		exit(ERROR);
	env_var_lst->str[0] = '$';
	env_var_lst->str[1] = '?';
	env_var_lst->str[2] = '\0';
}

static void	set_key_value_str(t_lst *lst, t_lst *env_var_lst, size_t len, \
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
	*i -= 1;
	env_var_lst->key[j] = '\0';
	env_var_lst->value = getenv(env_var_lst->key);
	env_var_lst->str = (char *)ft_calloc(len + 2, sizeof(char));
	if (!(env_var_lst->str))
		exit(ERROR);
	env_var_lst->str[0] = '$';
	j = 1;
	while (j < len + 1)
	{
		env_var_lst->str[j] = env_var_lst->key[j - 1];
		j++;
	}
	env_var_lst->str[j] = '\0';
}

static void	set_exit_status_at_syn(t_info *info, size_t *i)
{
	t_lst	*env_var_lst;

	*i += 1;
	env_var_lst = ft_lstnew(NULL);
	set_lst_info(info, env_var_lst, ENV_VAR_LST);
	env_var_lst->key = (char *)ft_calloc(2, sizeof(char));
	if (!(env_var_lst->key))
		exit(ERROR);
	set_key_value_str_for_exit_status(env_var_lst);
	ft_lstadd_back(&(info->sentence_lst->env_var_lst), env_var_lst);
}

static void	set_env_var_info(t_info *info, t_lst *lst, size_t *i)
{
	size_t	i_tmp;
	size_t	len;
	t_lst	*env_var_lst;

	len = 0;
	*i += 1;
	i_tmp = *i;
	while (lst->str[*i] != '\"' && lst->str[*i] != ' ' && \
		lst->str[*i] != '\0' && lst->str[*i] != '$')
	{
		len++;
		*i += 1;
	}
	*i = i_tmp;
	env_var_lst = ft_lstnew(NULL);
	set_lst_info(info, env_var_lst, ENV_VAR_LST);
	env_var_lst->key = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(env_var_lst->key))
		exit(ERROR);
	set_key_value_str(lst, env_var_lst, len, i);
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
			{
				if (lst->str[i + 1])
				{
					if (lst->str[i + 1] != '?')
						set_env_var_info(info, lst, &i);
					else
						set_exit_status_at_syn(info, &i);
				}
			}
			i++;
		}
	}
}
