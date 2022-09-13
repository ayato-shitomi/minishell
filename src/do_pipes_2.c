#include "../includes/minishell.h"

char	**get_envp_in_array(t_info *info)
{
	char			**envp;
	t_env_var_lst	*env_var_lst_tmp;
	size_t			i;

	env_var_lst_tmp = info->env_var_lst;
	envp = (char **)ft_calloc(ft_env_var_lstsize(info->env_var_lst) + 1, \
		sizeof(char *));
	if (!envp)
		exit(ERROR);
	i = 0;
	while (info->env_var_lst)
	{
		envp[i] = ft_strjoin_three(info->env_var_lst->key, "=", \
			info->env_var_lst->value);
		info->env_var_lst = info->env_var_lst->next;
		i++;
	}
	envp[i] = NULL;
	info->env_var_lst = env_var_lst_tmp;
	return (envp);
}

int	set_pipe_and_fork(int pipe_fd[2], pid_t *pid)
{
	if (pipe_and_error_check(pipe_fd) == ERROR)
		return (ERROR);
	if (fork_and_error_check(pid) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	set_sentence_lst_and_pipe_fd(t_info *info, \
	size_t cmd_cnt, int pipe_fd[2], size_t i)
{
	while (i++ < cmd_cnt - 1)
		info->sentence_lst = info->sentence_lst->next;
	if (set_pipe_fd_2(info, pipe_fd) == ERROR) //
		exit(ERROR);
	// if (set_pipe_fd_2(info->sentence_lst, pipe_fd) == ERROR)
	// 	exit(ERROR);
}

int	check_first_sentence(t_info *info, size_t i, \
	size_t cmd_cnt)
{
	if (i == cmd_cnt - 1)
		set_cmd_fd_and_exec(info, 0);
	return (SUCCESS);
}
