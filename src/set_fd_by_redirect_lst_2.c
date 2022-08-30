#include "../includes/minishell.h"

void	init_and_set_fd_for_restore(t_info *info, int n)
{
	if (info->fd_in_restore_flag)
	{
		dup2(info->fd_for_restore, 0);
		close(info->fd_for_restore);
		info->fd_in_restore_flag = 0;
	}
	else if (info->fd_out_restore_flag)
	{
		dup2(info->fd_for_restore, 1);
		close(info->fd_for_restore);
		info->fd_out_restore_flag = 0;
	}
	if (n == 0)
	{
		info->fd_for_restore = dup(n);
		info->fd_in_restore_flag = 1;
	}
	else if (n == 1)
	{
		info->fd_for_restore = dup(n);
		info->fd_out_restore_flag = 1;
	}
}

int	set_fd_case_red_right_two(t_info *info)
{
	int	fd_out;
	int	continue_flag;

	set_continue_flag(info->sentence_lst, &continue_flag);
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
	init_and_set_fd_for_restore(info, 1);
	dup2(fd_out, 1);
	close(fd_out);
	if (continue_flag == 1)
		info->red_left_after_right_flag = 1;
	else
		info->red_left_after_right_flag = 0;
	return (SUCCESS);
}

int	set_fd_case_red_right_one(t_info *info)
{
	int	fd_out;
	int	continue_flag;

	set_continue_flag(info->sentence_lst, &continue_flag);
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
	init_and_set_fd_for_restore(info, 1);
	dup2(fd_out, 1);
	close(fd_out);
	if (continue_flag == 1)
		info->red_left_after_right_flag = 1;
	else
		info->red_left_after_right_flag = 0;
	return (SUCCESS);
}

// int	set_fd_case_red_right_one(t_info *info) // 変更前
// {
// 	int	fd_out;

// 	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
// 	{
// 		if (access(info->sentence_lst->redirect_lst->str, W_OK) == -1)
// 		{
// 			perror(SHELLNAME);
// 			return (ERROR);
// 		}
// 	}
// 	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
// 		unlink(info->sentence_lst->redirect_lst->str);
// 	fd_out = open(info->sentence_lst->redirect_lst->str, O_WRONLY | O_CREAT, \
// 		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 	if (fd_out == -1)
// 	{
// 		perror(SHELLNAME);
// 		return (ERROR);
// 	}
// 	init_and_set_fd_for_restore(info, 1);
// 	dup2(fd_out, 1);
// 	close(fd_out);
// 	return (SUCCESS);
// }

int	set_fd_case_red_left_one(t_info *info)
{
	int	fd_in;
	int	continue_flag;

	set_continue_flag(info->sentence_lst, &continue_flag);
	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
	{
		if (access(info->sentence_lst->redirect_lst->str, R_OK) == -1)
			error_and_exit(info->sentence_lst->redirect_lst->str, \
				PERM_DENIED, ERROR);
	}
	else
		error_and_exit(info->sentence_lst->redirect_lst->str, NO_FILE, ERROR);
	fd_in = open(info->sentence_lst->redirect_lst->str, O_RDONLY);
	if (fd_in == -1)
	{
		perror(SHELLNAME);
		exit(ERROR);
	}
	if (!info->red_left_after_right_flag)
	{
		init_and_set_fd_for_restore(info, 0);
		dup2(fd_in, 0);
		close(fd_in);
		if (continue_flag == 1)
			init_and_set_fd_for_restore(info, 2);
	}
	else
		info->red_left_after_right_flag = 0;
	return (SUCCESS);
}

// int	set_fd_case_red_left_one(t_info *info) // 変更前
// {
// 	int	fd_in;

// 	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
// 	{
// 		if (access(info->sentence_lst->redirect_lst->str, R_OK) == -1)
// 			error_and_exit(info->sentence_lst->redirect_lst->str, \
// 				PERM_DENIED, ERROR);
// 	}
// 	else
// 		error_and_exit(info->sentence_lst->redirect_lst->str, NO_FILE, ERROR);
// 	fd_in = open(info->sentence_lst->redirect_lst->str, O_RDONLY);
// 	if (fd_in == -1)
// 	{
// 		perror(SHELLNAME);
// 		exit(ERROR);
// 	}
// 	init_and_set_fd_for_restore(info, 0);
// 	dup2(fd_in, 0);
// 	close(fd_in);
// 	return (SUCCESS);
// }
