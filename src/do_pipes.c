#include "../includes/minishell.h"

static char	*get_cmd_path(char **env_path, char **cmd)
{
	size_t	i;
	char	*cmd_path;

	i = 0;
	// info->is_first++;
	while (env_path[i])
	{
		if (cmd[0][0] == '/')
		{
			cmd_path = cmd[0];
			// info->is_no_free = 1;
		}
		else
			cmd_path = ft_strjoin_three(env_path[i++], "/", cmd[0]);
		if (access(cmd_path, F_OK) == 0 && cmd[0][0] != '\0')
			return (cmd_path);
		free(cmd_path);
	}
	// ft_putstr_fd("command not found: ", 2);
	// ft_putstr_fd(cmd[0], 2);
	// write(2, "\n", 1);
	// if (info->is_first == 0)
	// 	check_cmd_2(env_paths, info);
	exit(1);
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

int	do_pipes(t_sentence_lst *sentence_lst, size_t i, size_t cmd_cnt)
{
	pid_t		pid;
	int			pipe_fd[2];
	char		**cmd;
	char		**env_path;
	char		*env_path_value_tmp;
	char		*env_path_value;
	char		*cmd_path;
	extern char	**environ;

	env_path_value_tmp = getenv("PATH");
	env_path_value = ft_strdup(env_path_value_tmp);
	env_path = ft_split(env_path_value, ':');
	if (i == cmd_cnt - 1)
	{
		cmd = set_cmd_in_cmd_lst(sentence_lst);
		cmd_path = get_cmd_path(env_path, cmd);
		if (set_fd_by_redirect_lst(sentence_lst) == ERROR)
			return (ERROR);
		execve(cmd_path, cmd, environ);
	}
	else
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("bash");
			return (ERROR);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("bash");
			return (ERROR);
		}
		else if (pid == 0)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], 1);
			close(pipe_fd[1]);
			if (do_pipes(sentence_lst, i + 1, cmd_cnt) == ERROR)
				return (ERROR);
		}
		else
		{
			while (i < cmd_cnt - 1)
			{
				sentence_lst = sentence_lst->next;
				i++;
			}
			cmd = set_cmd_in_cmd_lst(sentence_lst);
			cmd_path = get_cmd_path(env_path, cmd);
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
			execve(cmd_path, cmd, environ);
		}
	}
	return (SUCCESS);
}
