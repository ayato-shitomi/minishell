/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_var_and_set_env_var_info.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/16 13:39:44 by mhida            ###   ########.fr       */
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

static void	set_key_value_str_1(t_info *info, t_lst *env_var_lst, size_t len, \
	size_t *i)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		env_var_lst->key[j] = info->token_dl_lst->token[*i];
		*i += 1;
		j++;
	}
	*i -= 1;
	env_var_lst->key[j] = '\0';
}

static void	set_env_var_info(t_info *info, size_t *i)
{
	size_t	i_tmp;
	size_t	len;
	t_lst	*env_var_lst;

	*i += 1;
	i_tmp = *i;
	len = get_env_var_len(info, i);
	*i = i_tmp;
	env_var_lst = ft_lstnew(NULL);
	set_lst_info(info, env_var_lst, ENV_VAR_LST);
	env_var_lst->key = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(env_var_lst->key))
		exit(ERROR);
	set_key_value_str_1(info, env_var_lst, len, i);
	set_key_value_str_2(env_var_lst, len);
	if (env_var_lst->token_type == NOT_EXPANDABLE)
		env_var_lst->value = ft_strdup(env_var_lst->str);
	else
		env_var_lst->value = get_env_value(info, env_var_lst->key);
	ft_lstadd_back(&(info->sentence_lst->env_var_lst), env_var_lst);
}

static int	set_flag_and_p(t_info *info, int *is_first_sentence)
{
	info->token_dl_lst = info->token_dl_lst->next;
	if (info->token_dl_lst->dl_lst_first_flag)
		return (1);
	if (info->token_dl_lst->type == PIPE)
	{
		info->sentence_lst = info->sentence_lst->next;
		*is_first_sentence = 0;
	}
	return (0);
}

void	check_env_var_and_set_env_var_info(t_info *info)
{
	size_t	i;
	int		is_first_sentence;

	is_first_sentence = 1;
	while (info->sentence_lst)
	{
		i = 0;
		while (info->token_dl_lst->token[i])
		{
			if (info->token_dl_lst->token[i] == '$')
			{
				if (info->token_dl_lst->token[i + 1])
				{
					if (info->token_dl_lst->token[i + 1] != '?' \
						&& info->token_dl_lst->token[i + 1] != '$')
						set_env_var_info(info, &i);
					else if (info->token_dl_lst->token[i + 1] != '$')
						set_exit_status_first(info, &i, is_first_sentence);
				}
			}
			i++;
		}
		if (set_flag_and_p(info, &is_first_sentence) == 1)
			return ;
	}
}
