#include "../includes/minishell.h"

int	set_pipe_fd_2(t_info *info, int pipe_fd[2])
{
	if (!info->sentence_lst->redirect_lst)
	{
		if (dup2(pipe_fd[0], 0) == -1)
		{
			perror(SHELLNAME);
			return (ERROR);
		}
		if (close(pipe_fd[0]) == -1)
		{
			perror(SHELLNAME);
			return (ERROR);
		}
		init_and_set_fd_for_restore(info, 0);
		// info->fd_for_restore_in = dup(0); //
	}
	else
	{
		if (info->sentence_lst->redirect_lst->token_type != REDIRECT_LEFT_TWO)
		{
			if (dup2(pipe_fd[0], 0) == -1)
			{
				perror(SHELLNAME);
				return (ERROR);
			}
			if (close(pipe_fd[0]) == -1)
			{
				perror(SHELLNAME);
				return (ERROR);
			}
		}
	}
	if (close(pipe_fd[1]) == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	return (SUCCESS);
}

// int	set_pipe_fd_2(t_sentence_lst *sentence_lst, int pipe_fd[2]) // before modification
// {
// 	if (!sentence_lst->redirect_lst)
// 	{
// 		if (dup2(pipe_fd[0], 0) == -1)
// 		{
// 			perror(SHELLNAME);
// 			return (ERROR);
// 		}
// 		if (close(pipe_fd[0]) == -1)
// 		{
// 			perror(SHELLNAME);
// 			return (ERROR);
// 		}
// 	}
// 	else
// 	{
// 		if (sentence_lst->redirect_lst->token_type != REDIRECT_LEFT_TWO)
// 		{
// 			if (dup2(pipe_fd[0], 0) == -1)
// 			{
// 				perror(SHELLNAME);
// 				return (ERROR);
// 			}
// 			if (close(pipe_fd[0]) == -1)
// 			{
// 				perror(SHELLNAME);
// 				return (ERROR);
// 			}
// 		}
// 	}
// 	if (close(pipe_fd[1]) == -1)
// 	{
// 		perror(SHELLNAME);
// 		return (ERROR);
// 	}
// 	return (SUCCESS);
// }

int	set_pipe_fd_1(int pipe_fd[2])
{
	if (close(pipe_fd[0]) == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	if (dup2(pipe_fd[1], 1) == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	if (close(pipe_fd[1]) == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	return (SUCCESS);
}

int	set_pipe_fd_0(int pipe_fd[2])
{
	if (close(pipe_fd[1]) == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	if (dup2(pipe_fd[0], 0) == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	if (close(pipe_fd[0]) == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	return (SUCCESS);
}
