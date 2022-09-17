/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/17 19:26:06 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	validate_arg_at_ft_export_2(t_info *info, t_lst	*cmd_lst_tmp)
{
	char	*joined_arg;

	joined_arg = ft_strjoin_three("`", info->sentence_lst->cmd_lst->str, \
		"'");
	error_and_return("export", joined_arg, NOT_VI);
	free(joined_arg);
	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	return (ERROR);
}

static int	check_validate_err(t_info *info, char **split_str, \
	t_lst	*cmd_lst_tmp, size_t i)
{
	char	*joined_arg;

	if (!split_str[0])
	{
		joined_arg = ft_strjoin_three("`", info->sentence_lst->cmd_lst->str, \
			"'");
		error_and_return("export", joined_arg, NOT_VI);
		ft_free_cmd(split_str);
		free(joined_arg);
		info->sentence_lst->cmd_lst = cmd_lst_tmp;
		return (ERROR);
	}
	else if (ft_isalnum(split_str[0][i]) == 0 && split_str[0][i] != '_')
	{
		joined_arg = ft_strjoin_three("`", info->sentence_lst->cmd_lst->str, \
			"'");
		error_and_return("export", joined_arg, NOT_VI);
		ft_free_cmd(split_str);
		free(joined_arg);
		info->sentence_lst->cmd_lst = cmd_lst_tmp;
		return (ERROR);
	}
	return (SUCCESS);
}

static int	loop_to_validate(t_info *info, char **split_str, \
	t_lst *cmd_lst_tmp, size_t i)
{
	while (split_str[0][i])
	{
		if (check_validate_err(info, split_str, cmd_lst_tmp, i) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	validate_arg_at_ft_export(t_info *info)
{
	t_lst	*cmd_lst_tmp;
	char	**split_str;
	size_t	i;

	cmd_lst_tmp = info->sentence_lst->cmd_lst;
	info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
	while (info->sentence_lst->cmd_lst)
	{
		if (info->sentence_lst->cmd_lst->str)
			if (info->sentence_lst->cmd_lst->str[0] == '=' \
				|| ft_isnum(info->sentence_lst->cmd_lst->str[0]))
				return (validate_arg_at_ft_export_2(info, cmd_lst_tmp));
		split_str = ft_split(info->sentence_lst->cmd_lst->str, '=');
		i = 0;
		if (!split_str[0])
			if (check_validate_err(info, split_str, cmd_lst_tmp, i) == ERROR)
				return (ERROR);
		if (loop_to_validate(info, split_str, cmd_lst_tmp, i) == ERROR)
			return (ERROR);
		ft_free_cmd(split_str);
		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
	}
	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	return (SUCCESS);
}
