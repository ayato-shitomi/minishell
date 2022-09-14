/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 10:22:07 by mhida             #+#    #+#             */
/*   Updated: 2022/09/14 11:24:58 by mhida            ###   ########.fr       */
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
		if (sentence_lst->redirect_lst->next->token_type == \
				REDIRECT_LEFT_TWO || \
			sentence_lst->redirect_lst->next->token_type == \
				REDIRECT_LEFT_ONE)
			*continue_flag = 1;
	}
}

static int	flag_check(int flag)
{
	if (flag == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	return (SUCCESS);
}

void	do_gnl(int flag, char **line)
{
	flag = get_next_line(0, line);
	if (flag_check(flag) == ERROR)
		exit(ERROR);
}

int	open_fd_and_calloc(int *tmp_fd, \
	char **cat_line, int *flag, char *tmp_file)
{
	*tmp_fd = open(tmp_file, O_RDWR | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*tmp_fd == -1)
	{
		perror(SHELLNAME);
		return (ERROR);
	}
	*cat_line = (char *)ft_calloc(1, sizeof(char));
	if (!(*cat_line))
		exit(ERROR);
	*flag = 1;
	return (SUCCESS);
}
