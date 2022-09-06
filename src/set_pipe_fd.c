#include "../includes/minishell.h"

int	set_pipe_fd_2(t_sentence_lst *sentence_lst, int pipe_fd[2])
{
	if (!sentence_lst->redirect_lst)
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
	else
	{
		if (sentence_lst->redirect_lst->token_type != REDIRECT_LEFT_TWO)
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
