/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:22:07 by mhida             #+#    #+#             */
/*   Updated: 2022/09/19 15:24:52 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_tmp_file(char **tmp_file)
{
	int	n;

	n = 0;
	while (1)
	{
		*tmp_file = ft_itoa(n);
		if (access(*tmp_file, F_OK) != 0)
			break ;
		free(*tmp_file);
		if (n == INT_MAX)
			exit(ERROR);
		n++;
	}
}

void	set_continue_flag(t_sentence_lst *sentence_lst, int *continue_flag)
{
	*continue_flag = 0;
	if (sentence_lst->redirect_lst->next)
	{
		if (sentence_lst->redirect_lst->next->token_type >= REDIRECT_LEFT_ONE \
		&& sentence_lst->redirect_lst->next->token_type <= REDIRECT_RIGHT_TWO)
			*continue_flag = 1;
	}
}

int	do_readline(t_info *info, char **command)
{
	init_and_set_fd_for_restore(info, 2);
	*command = readline("> ");
	if (!(*command))
		return (ERROR);
	return (SUCCESS);
}

int	open_fd_and_calloc(int *tmp_fd, \
	char **cat_line, char *tmp_file)
{
	*tmp_fd = open(tmp_file, O_RDWR | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*tmp_fd == -1)
		return (rtn_error());
	*cat_line = (char *)ft_calloc(1, sizeof(char));
	if (!(*cat_line))
		exit(ERROR);
	return (SUCCESS);
}
