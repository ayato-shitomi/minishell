#include "../includes/minishell.h"

void	set_pipe_fd_2(t_sentence_lst *sentence_lst, int pipe_fd[2])
{
	if (!sentence_lst->redirect_lst)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
	else
	{
		if (sentence_lst->redirect_lst->token_type != REDIRECT_LEFT_TWO)
		{
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
		}
	}
	close(pipe_fd[1]);
}

void	set_pipe_fd_1(int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
}

void	set_pipe_fd_0(int pipe_fd[2])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}
