#include "../includes/minishell.h"

static char	*get_cmd_path(char **env_path, char **cmd)
{
	size_t	i;
	char	*cmd_path;

	i = 0;
	while (env_path[i])
	{
		if (cmd[0][0] == '/')
			cmd_path = cmd[0];
		else
			cmd_path = ft_strjoin_three(env_path[i++], "/", cmd[0]);
		if (access(cmd_path, F_OK) == 0 && cmd[0][0] != '\0')
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

static char	**set_cmd_in_cmd_lst(t_sentence_lst *sentence_lst)
{
	size_t	i;
	size_t	cmd_lst_cnt;
	size_t	len;
	t_lst	*cmd_lst_tmp;
	char	**cmd;

	cmd_lst_tmp = sentence_lst->cmd_lst;
	cmd_lst_cnt = ft_lstsize(sentence_lst->cmd_lst);
	cmd = (char **)ft_calloc(cmd_lst_cnt + 1, sizeof(char *));
	if (!cmd)
		exit(ERROR);
	i = 0;
	while (i < cmd_lst_cnt)
	{
		len = ft_strlen(sentence_lst->cmd_lst->str);
		cmd[i] = (char *)ft_calloc(len + 1, sizeof(char));
		if (!cmd[i])
			exit(ERROR);
		ft_strcpy(cmd[i], sentence_lst->cmd_lst->str);
		sentence_lst->cmd_lst = sentence_lst->cmd_lst->next;
		i++;
	}
	cmd[i] = NULL;
	sentence_lst->cmd_lst = cmd_lst_tmp;
	return (cmd);
}

static int	set_cmd_and_fd(t_sentence_lst *sentence_lst, char **env_path, \
	char ***cmd, char **cmd_path)
{
	*cmd = set_cmd_in_cmd_lst(sentence_lst);
	*cmd_path = get_cmd_path(env_path, *cmd);
	if (set_fd_by_redirect_lst(sentence_lst) == ERROR)
		return (ERROR);
	return (SUCCESS);
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

int	do_pipes(t_sentence_lst *sentence_lst, size_t i, size_t cmd_cnt, \
	char **environ)
{
	pid_t		pid;
	int			pipe_fd[2];
	char		**cmd;
	char		*cmd_path;
	char		**env_path;

	env_path = get_env_path();
	if (!env_path)
		return (ERROR);
	if (i == cmd_cnt - 1)
	{
		set_cmd_and_fd(sentence_lst, env_path, &cmd, &cmd_path);
		execve(cmd_path, cmd, environ);
	}
	else
	{
		if (pipe_and_error_check(pipe_fd) == ERROR)
			return (ERROR);
		if (fork_and_error_check(&pid) == ERROR)
			return (ERROR);
		else if (pid == 0)
		{
			set_pipe_fd_1(pipe_fd);
			if (do_pipes(sentence_lst, i + 1, cmd_cnt, environ) == ERROR)
				return (ERROR);
		}
		else
		{
			while (i++ < cmd_cnt - 1)
				sentence_lst = sentence_lst->next;
			set_pipe_fd_2(sentence_lst, pipe_fd);
			if (set_cmd_and_fd(sentence_lst, env_path, &cmd, &cmd_path) == ERROR)
				return (ERROR);
			execve(cmd_path, cmd, environ);
		}
	}
	return (SUCCESS);
}
