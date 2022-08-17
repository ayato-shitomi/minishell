#include "../includes/minishell.h"

int	set_fd_case_red_right_two(t_info *info)
{
	int	fd_out;

	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
	{
		if (access(info->sentence_lst->redirect_lst->str, W_OK) == -1)
		{
			perror(SHELLNAME);
			return (ERROR);
		}
	}
	fd_out = open(info->sentence_lst->redirect_lst->str, \
		O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	dup2(fd_out, 1);
	close(fd_out);
	return (SUCCESS);
}

int	set_fd_case_red_right_one(t_info *info)
{
	int	fd_out;

	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
	{
		if (access(info->sentence_lst->redirect_lst->str, W_OK) == -1)
		{
			perror(SHELLNAME);
			return (ERROR);
		}
	}
	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
		unlink(info->sentence_lst->redirect_lst->str);
	fd_out = open(info->sentence_lst->redirect_lst->str, O_WRONLY | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	dup2(fd_out, 1);
	close(fd_out);
	return (SUCCESS);
}

int	set_fd_case_red_left_one(t_info *info)
{
	int	fd_in;

	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
	{
		if (access(info->sentence_lst->redirect_lst->str, R_OK) == -1)
		{
			perror(SHELLNAME);
			return (ERROR);
		}
	}
	else
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	fd_in = open(info->sentence_lst->redirect_lst->str, O_RDONLY);
	if (fd_in == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	dup2(fd_in, 0);
	close(fd_in);
	return (SUCCESS);
}
