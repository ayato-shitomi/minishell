/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_the_expandable_in_cmd_lst.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/16 12:07:53 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_p_2_in_cmd_lst(t_info *info, char **str_front_p, \
	char **str_back_p, char *str_p)
{
	size_t	i;
	size_t	env_var_str_len;
	size_t	rest_front_len;
	size_t	rest_back_len;

	env_var_str_len = ft_strlen(info->sentence_lst->env_var_lst->str);
	rest_back_len = ft_strlen((str_p + env_var_str_len));
	rest_front_len = ft_strlen(info->sentence_lst->cmd_lst->str) \
		- env_var_str_len - rest_back_len;
	*str_front_p = (char *)ft_calloc(rest_front_len + 1, sizeof(char));
	*str_back_p = (char *)ft_calloc(rest_back_len + 1, sizeof(char));
	if (!(*str_front_p) || !(*str_back_p))
		exit(ERROR);
	i = 0;
	while (i++ < rest_front_len)
		(*str_front_p)[i - 1] = info->sentence_lst->cmd_lst->str[i - 1];
	(*str_front_p)[i - 1] = '\0';
	i = 0;
	while (i < rest_back_len)
	{
		(*str_back_p)[i] = str_p[i + env_var_str_len];
		i++;
	}
	(*str_back_p)[i] = '\0';
}

static void	set_p_1_in_cmd_lst(t_info *info, char **str_env_value_p)
{
	size_t	i;
	size_t	env_var_value_len;

	if (info->sentence_lst->env_var_lst->value)
		env_var_value_len = ft_strlen(info->sentence_lst->env_var_lst->value);
	else
		env_var_value_len = 0;
	*str_env_value_p = (char *)ft_calloc(env_var_value_len + 1, sizeof(char));
	if (!(*str_env_value_p))
		exit(ERROR);
	i = 0;
	while (i < env_var_value_len)
	{
		(*str_env_value_p)[i] = info->sentence_lst->env_var_lst->value[i];
		i++;
	}
	(*str_env_value_p)[i] = '\0';
}

static char	*get_str_p_in_cmd_lst(t_info *info, char *str_p, int flag)
{
	char	*str_p_dup;
	char	*str_p_tmp;

	str_p_dup = NULL;
	if (flag == 0)
	{
		if (info->sentence_lst->env_var_lst)
		{
			str_p_tmp = ft_strnstr(info->sentence_lst->cmd_lst->str, \
				info->sentence_lst->env_var_lst->str, \
				ft_strlen(info->sentence_lst->cmd_lst->str));
			str_p_dup = ft_strdup(str_p_tmp);
		}
	}
	else if (flag == 1)
	{
		str_p_tmp = ft_strnstr(str_p + \
			ft_strlen(info->sentence_lst->env_var_lst->key) + 1, \
			info->sentence_lst->env_var_lst->next->str, ft_strlen(str_p + \
				ft_strlen(info->sentence_lst->env_var_lst->key) + 1));
		str_p_dup = ft_strdup(str_p_tmp);
		free(str_p);
	}
	return (str_p_dup);
}

static char	*change_p_in_cmd_lst(t_info *info, char *str_p)
{
	str_p = get_str_p_in_cmd_lst(info, str_p, 1);
	info->sentence_lst->env_var_lst = \
		info->sentence_lst->env_var_lst->next;
	return (str_p);
}

int	expand_the_expandable_in_cmd_lst(t_info *info)
{
	char	*str_p;
	char	*str_env_value_p;
	char	*str_front_p;
	char	*str_back_p;

	str_p = NULL;
	str_p = get_str_p_in_cmd_lst(info, str_p, 0);
	while (str_p)
	{
		set_p_1_in_cmd_lst(info, &str_env_value_p);
		set_p_2_in_cmd_lst(info, &str_front_p, &str_back_p, str_p);
		free(info->sentence_lst->cmd_lst->str);
		info->sentence_lst->cmd_lst->str = \
			ft_strjoin_three(str_front_p, str_env_value_p, str_back_p);
		if (info->sentence_lst->env_var_lst->next)
			str_p = change_p_in_cmd_lst(info, str_p);
		else
		{
			ft_free_p(str_env_value_p, str_front_p, str_back_p, str_p);
			return (1);
		}
		ft_free_p(str_env_value_p, str_front_p, str_back_p, str_p);
	}
	return (0);
}

/*
static void	set_p_1_in_cmd_lst(t_info *info, char **str_env_value_p)
{
	size_t	i;
	size_t	j;
	size_t	env_var_value_len;

	// if (ft_strncmp(info->sentence_lst->env_var_lst->str, "$?", 2) == 0)
	// 	info->sentence_lst->env_var_lst->value = ft_strdup();
	// else
	// 	info->sentence_lst->env_var_lst->value = \
	// 		getenv(info->sentence_lst->env_var_lst->key);
	if (info->sentence_lst->env_var_lst->value)
		env_var_value_len = ft_strlen(info->sentence_lst->env_var_lst->value);
	else
		env_var_value_len = 0;
	*str_env_value_p = (char *)ft_calloc(env_var_value_len + 1, sizeof(char));
	if (!(*str_env_value_p))
		exit(ERROR);
	i = 0;
	j = 0;
	while (i < env_var_value_len)
	{
		(*str_env_value_p)[i] = info->sentence_lst->env_var_lst->value[j];
		i++;
		j++;
	}
	(*str_env_value_p)[i] = '\0';
}
*/
