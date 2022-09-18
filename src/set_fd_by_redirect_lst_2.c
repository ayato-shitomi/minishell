/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_by_redirect_lst_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:28 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/18 22:00:05 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	set_fd_case_red_right(t_info *info, int fd_out, \
	int continue_flag)
{
	if (init_and_set_fd_for_restore(info, 1) == ERROR)
		return (rtn_error());
	if (dup2(fd_out, 1) == -1)
		return (rtn_error());
	if (close(fd_out) == -1)
		return (rtn_error());
	if (continue_flag == 1 && \
	(info->sentence_lst->redirect_lst->next->token_type == REDIRECT_RIGHT_ONE \
	|| info->sentence_lst->redirect_lst->next->token_type \
	== REDIRECT_RIGHT_TWO))
	{
		if (check_fd_in_flag_and_restore_fd_in_and_out(info) == ERROR)
			return (ERROR);
	}
	else if (continue_flag == 1 && \
	(info->sentence_lst->redirect_lst->next->token_type == REDIRECT_LEFT_ONE \
	|| info->sentence_lst->redirect_lst->next->token_type == REDIRECT_LEFT_TWO))
	{
		info->fd_out_restore_flag = 0;
		if (init_and_set_fd_for_restore(info, 2) == ERROR)
			return (rtn_error());
		info->fd_out_restore_flag = 1;
	}
	return (SUCCESS);
}

int	set_fd_case_red_right_two(t_info *info)
{
	int	fd_out;
	int	continue_flag;

	set_continue_flag(info->sentence_lst, &continue_flag);
	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
	{
		if (access(info->sentence_lst->redirect_lst->str, W_OK) == -1)
			return (error_and_return(info->sentence_lst->redirect_lst->str, \
				NULL, PERM_DENIED));
	}
	fd_out = open(info->sentence_lst->redirect_lst->str, \
		O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out == -1)
		return (rtn_error());
	if (set_fd_case_red_right(info, fd_out, continue_flag) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	set_fd_case_red_right_one(t_info *info)
{
	int	fd_out;
	int	continue_flag;

	set_continue_flag(info->sentence_lst, &continue_flag);
	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
		if (access(info->sentence_lst->redirect_lst->str, W_OK) == -1)
			return (error_and_return(info->sentence_lst->redirect_lst->str, \
				NULL, PERM_DENIED));
	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
		if (unlink(info->sentence_lst->redirect_lst->str) == -1)
			return (rtn_error());
	fd_out = open(info->sentence_lst->redirect_lst->str, O_WRONLY | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd_out == -1)
		return (rtn_error());
	if (set_fd_case_red_right(info, fd_out, continue_flag) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	set_fd_case_red_left_one_2(t_info *info, int fd_in, \
	int continue_flag)
{
	if (init_and_set_fd_for_restore(info, 0) == ERROR)
		return (rtn_error());
	if (dup2(fd_in, 0) == -1)
		return (rtn_error());
	if (close(fd_in) == -1)
		return (rtn_error());
	if (continue_flag == 1 && \
	(info->sentence_lst->redirect_lst->next->token_type == REDIRECT_LEFT_ONE \
	|| info->sentence_lst->redirect_lst->next->token_type == REDIRECT_LEFT_TWO))
	{
		if (check_fd_out_flag_and_restore_fd_in_and_out(info) == ERROR)
			return (ERROR);
	}
	else if (continue_flag == 1 && \
	(info->sentence_lst->redirect_lst->next->token_type == REDIRECT_RIGHT_ONE \
	|| info->sentence_lst->redirect_lst->next->token_type \
	== REDIRECT_RIGHT_TWO))
	{
		info->fd_in_restore_flag = 0;
		if (init_and_set_fd_for_restore(info, 2) == ERROR)
			return (rtn_error());
		info->fd_in_restore_flag = 1;
	}
	return (SUCCESS);
}

int	set_fd_case_red_left_one(t_info *info)
{
	int	fd_in;
	int	continue_flag;

	set_continue_flag(info->sentence_lst, &continue_flag);
	if (access(info->sentence_lst->redirect_lst->str, F_OK) == 0)
	{
		if (access(info->sentence_lst->redirect_lst->str, R_OK) == -1)
			return (error_and_return(info->sentence_lst->redirect_lst->str, \
				NULL, PERM_DENIED));
	}
	else
		return (error_and_return(info->sentence_lst->redirect_lst->str, \
			NULL, NO_FILE));
	fd_in = open(info->sentence_lst->redirect_lst->str, O_RDONLY);
	if (fd_in == -1)
		return (rtn_error());
	if (set_fd_case_red_left_one_2(info, fd_in, continue_flag) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
