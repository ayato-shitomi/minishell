/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:28 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	validate_arg_at_ft_export_2(t_info *info, char **split_str, \
	t_lst	*cmd_lst_tmp, size_t i)
{
	char	*joined_arg;

	if (ft_isalnum(split_str[0][i]) == 0 && split_str[0][i] != '_')
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

int	validate_arg_at_ft_export(t_info *info)
{
	t_lst	*cmd_lst_tmp;
	char	**split_str;
	size_t	i;

	cmd_lst_tmp = info->sentence_lst->cmd_lst;
	info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
	while (info->sentence_lst->cmd_lst)
	{
		split_str = ft_split(info->sentence_lst->cmd_lst->str, '=');
		i = 0;
		while (split_str[0][i])
		{
			if (validate_arg_at_ft_export_2(info, split_str, cmd_lst_tmp, i) \
				== ERROR)
				return (ERROR);
			i++;
		}
		ft_free_cmd(split_str);
		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
	}
	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	return (SUCCESS);
}
