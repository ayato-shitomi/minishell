/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:27 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	get_ac_2(t_info *info)
{
	size_t	ac;
	t_lst	*cmd_lst_tmp;

	cmd_lst_tmp = info->sentence_lst->cmd_lst;
	ac = 0;
	while (info->sentence_lst->cmd_lst)
	{
		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
		ac++;
	}
	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	return (ac);
}

static size_t	get_ac(char **cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

// run built-in without pipes
int	exec_builtin_without_pipe(t_info *info)
{
	int		status;
	size_t	ac;

	status = SUCCESS;
	ac = get_ac_2(info);
	if (ft_strcmp(info->sentence_lst->cmd_lst->str, "cd") == 0)
		status = ft_cd(info);
	else if (ft_strcmp(info->sentence_lst->cmd_lst->str, "pwd") == 0)
		status = ft_pwd(info);
	else if (ft_strcmp(info->sentence_lst->cmd_lst->str, "env") == 0)
		status = ft_env(info);
	else if (ft_strcmp(info->sentence_lst->cmd_lst->str, "echo") == 0)
		status = ft_echo(info);
	else if (ft_strcmp(info->sentence_lst->cmd_lst->str, "exit") == 0)
		status = ft_exit(ac, NULL, info->sentence_lst->cmd_lst);
	else if (ft_strcmp(info->sentence_lst->cmd_lst->str, "unset") == 0)
		status = ft_unset(info);
	else if (ft_strcmp(info->sentence_lst->cmd_lst->str, "export") == 0)
		status = ft_export(info);
	return (status);
}

// run built-in woth pipes
int	exec_builtin(t_info *info, char **cmd)
{
	int		status;
	size_t	ac;

	status = SUCCESS;
	ac = get_ac(cmd);
	if (ft_strcmp(cmd[0], "cd") == 0)
		status = ft_cd(info);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		status = ft_pwd(info);
	else if (ft_strcmp(cmd[0], "env") == 0)
		status = ft_env(info);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		status = ft_echo(info);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		status = ft_exit(ac, cmd, NULL);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		status = ft_unset(info);
	else if (ft_strcmp(cmd[0], "export") == 0)
		status = ft_export(info);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		status = ft_unset(info);
	return (status);
}

int	check_builtin(char **cmd)
{
	if ((ft_strcmp(cmd[0], "cd") == 0) || \
	(ft_strcmp(cmd[0], "pwd") == 0) || \
	(ft_strcmp(cmd[0], "env") == 0) || \
	(ft_strcmp(cmd[0], "echo") == 0) || \
	(ft_strcmp(cmd[0], "exit") == 0) || \
	(ft_strcmp(cmd[0], "unset") == 0) || \
	(ft_strcmp(cmd[0], "export") == 0))
		return (1);
	return (0);
}
