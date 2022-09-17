/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipes_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 07:19:45 by mhida             #+#    #+#             */
/*   Updated: 2022/09/17 20:06:34 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_absolute_cmd(char **cmd)
{
	if (access(cmd[0], F_OK) == 0)
	{
		if (access(cmd[0], X_OK) == -1)
			error_and_exit(cmd[0], PERM_DENIED, E_STATUS_PERM_D);
		execve(cmd[0], cmd, NULL);
	}
}

static int	set_cmd_fd_and_exec_2(t_info *info, pid_t pid)
{
	int		status;
	pid_t	w_pid;

	w_pid = waitpid(pid, &status, WUNTRACED);
	if ((status != SUCCESS) && (g_exit_status == SIGINT))
	{
		init_and_set_fd_for_restore(info, 2);
		if (status % 256 == 0)
			exit(1);
		else
			exit(status);
	}
	return (SUCCESS);
}

int	set_cmd_fd_and_exec(t_info *info, pid_t pid)
{
	char		**env_path;
	char		**cmd;
	char		*cmd_path;
	int			status;
	char		**envp;

	if (pid > 0)
		status = set_cmd_fd_and_exec_2(info, pid);
	if (set_fd_by_redirect_lst(info, 0) == ERROR)
		exit(ERROR);
	cmd = set_cmd_in_cmd_lst(info);
	env_path = get_env_path(info, cmd);
	cmd_path = get_cmd_path(env_path, cmd);
	if (check_builtin(cmd))
	{
		status = exec_builtin(info, cmd);
		exit(status);
	}
	envp = get_envp_in_array(info);
	if (cmd[0])
		execve(cmd_path, cmd, envp);
	exit(SUCCESS);
}
