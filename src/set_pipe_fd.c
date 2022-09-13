/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:28 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	rtn_error(void)
{
	perror(SHELLNAME);
	return (ERROR);
}

int	set_pipe_fd_2(t_info *info, int pipe_fd[2])
{
	if (!info->sentence_lst->redirect_lst)
	{
		if (dup2(pipe_fd[0], 0) == -1)
			return (rtn_error());
		if (close(pipe_fd[0]) == -1)
			return (rtn_error());
		init_and_set_fd_for_restore(info, 0);
	}
	else
	{
		if (info->sentence_lst->redirect_lst->token_type != REDIRECT_LEFT_TWO)
		{
			if (dup2(pipe_fd[0], 0) == -1)
				return (rtn_error());
			if (close(pipe_fd[0]) == -1)
				return (rtn_error());
		}
	}
	if (close(pipe_fd[1]) == -1)
		return (rtn_error());
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

/*
// before modification
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
*/
