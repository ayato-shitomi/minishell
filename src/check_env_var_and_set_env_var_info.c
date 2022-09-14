/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var_and_set_env_var_info.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/15 05:51:19 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_key_value_str_2(t_lst *env_var_lst, size_t len)
{
	size_t	j;

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

static void	set_key_value_str_1(t_lst *lst, t_lst *env_var_lst, size_t len, \
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
}

static void	set_env_var_info(t_info *info, t_lst *lst, size_t *i)
{
	size_t	i_tmp;
	size_t	len;
	t_lst	*env_var_lst;

	len = 0;
	*i += 1;
	i_tmp = *i;
	while (lst->str[*i] != '\"' && lst->str[*i] != '\'' && \
		lst->str[*i] != ' ' && lst->str[*i] != '\0' && lst->str[*i] != '$')
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
	set_key_value_str_1(lst, env_var_lst, len, i);
	env_var_lst->value = get_env_value(info, env_var_lst->key);
	set_key_value_str_2(env_var_lst, len);
	ft_lstadd_back(&(info->sentence_lst->env_var_lst), env_var_lst);
}

void	check_env_var_and_set_env_var_info(
	t_info *info, t_lst *lst, int is_first_sentence)
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
					if (lst->str[i + 1] != '?' && lst->str[i + 1] != '$')
						set_env_var_info(info, lst, &i);
					else if (lst->str[i + 1] != '$')
						set_exit_status_first(info, &i, is_first_sentence);
				}
			}
			i++;
		}
	}
}
