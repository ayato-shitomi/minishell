#include "../includes/minishell.h"

static char	*get_cmd_path(char **env_path, char **cmd)
{
	size_t	i;
	char	*cmd_path;

	i = 0;
	while (env_path[i])
	{
		if (cmd[0][0] == '/' || cmd[0][0] == '.')
			cmd_path = cmd[0];
		else
			cmd_path = ft_strjoin_three(env_path[i++], "/", cmd[0]);
		if (access(cmd_path, F_OK) == 0 && cmd[0][0] != '\0')
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

static char	**set_cmd_in_cmd_lst(t_info *info)
{
	size_t	i;
	size_t	cmd_lst_cnt;
	size_t	len;
	t_lst	*cmd_lst_tmp;
	char	**cmd;

	cmd_lst_tmp = info->sentence_lst->cmd_lst;
	cmd_lst_cnt = ft_lstsize(info->sentence_lst->cmd_lst);
	cmd = (char **)ft_calloc(cmd_lst_cnt + 1, sizeof(char *));
	if (!cmd)
		exit(ERROR);
	i = 0;
	while (i < cmd_lst_cnt)
	{
		len = ft_strlen(info->sentence_lst->cmd_lst->str);
		cmd[i] = (char *)ft_calloc(len + 1, sizeof(char));
		if (!cmd[i])
			exit(ERROR);
		ft_strcpy(cmd[i], info->sentence_lst->cmd_lst->str);
		info->sentence_lst->cmd_lst = info->sentence_lst->cmd_lst->next;
		i++;
	}
	cmd[i] = NULL;
	info->sentence_lst->cmd_lst = cmd_lst_tmp;
	return (cmd);
}

static char	**get_env_path(void)
{
	char		*env_path_value_tmp;
	char		*env_path_value;
	char		**env_path;

	env_path_value_tmp = getenv("PATH");
	env_path_value = ft_strdup(env_path_value_tmp);
	env_path = ft_split(env_path_value, ':');
	return (env_path);
}

int	set_cmd_fd_and_exec(t_info *info, char **envp, pid_t pid)
{
	char		**env_path;
	char		**cmd;
	char		*cmd_path;
	pid_t		w_pid;
	int			status;

	env_path = get_env_path();
	if (!env_path)
		exit(ERROR);
	cmd = set_cmd_in_cmd_lst(info);
	cmd_path = get_cmd_path(env_path, cmd); // ビルトインの場合cmd_pathを取得しないように変更する!
	if (!cmd_path)
		error_and_exit(cmd[0], CMD_NOT_FOUND, E_STATUS_CNF);
	if (pid > 0)
	{
		w_pid = waitpid(pid, &status, WUNTRACED);
		// if (WEXITSTATUS(status) != 0)
		// 	exit(WEXITSTATUS(status));
	}
	if (set_fd_by_redirect_lst(info) == ERROR)
		return (ERROR);
	check_builtin(cmd);
	execve(cmd_path, cmd, envp);
	return (ERROR);
}

int	do_pipes(t_info *info, size_t i, size_t cmd_cnt, char **envp)
{
	pid_t		pid;
	int			pipe_fd[2];

	if (check_first_sentence(info, i, cmd_cnt, envp) == ERROR)
		exit(ERROR);
	else
	{
		if (set_pipe_and_fork(pipe_fd, &pid) == ERROR)
			return (ERROR);
		else if (pid == 0)
		{
			set_pipe_fd_1(pipe_fd);
			if (do_pipes(info, i + 1, cmd_cnt, envp) == ERROR)
				exit(ERROR);
		}
		else
		{
			set_sentence_lst_and_pipe_fd(info, cmd_cnt, pipe_fd, i);
			if (set_cmd_fd_and_exec(info, envp, pid) == ERROR)
				exit(ERROR);
		}
	}
	return (SUCCESS);
}
