/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:27 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int rtn_error(void)
{
	perror(SHELLNAME);
	return (ERROR);
}

static int	set_pipe_fd_and_write(int heredoc_pipe_fd[2], int tmp_fd, \
	char *cat_line, char *line, char *tmp_file)
{
	if (close(heredoc_pipe_fd[0]) == -1)
		return (rtn_error());
	if (dup2(heredoc_pipe_fd[1], tmp_fd) == -1)
		return (rtn_error());
	if (close(heredoc_pipe_fd[1]) == -1)
		return (rtn_error());
	write(tmp_fd, cat_line, ft_strlen(cat_line));
	if (close(tmp_fd) == -1)
		return (rtn_error());
	if (tmp_file)
	{
		if (unlink(tmp_file) == -1)
			return (rtn_error());
		free(tmp_file);
	}
	free(line);
	free(cat_line);
	exit(SUCCESS);
}

static char	*set_cat_line(t_sentence_lst *sentence_lst, \
	char *cat_line, char *line)
{
	char	*cat_line_tmp;

	cat_line_tmp = cat_line;
	if (ft_strcmp(line, sentence_lst->redirect_lst->str) != 0)
	{
		cat_line = ft_strjoin_three(cat_line, line, "\n");
		free(cat_line_tmp);
	}
	return (cat_line);
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

// static int	open_fd_and_calloc(int *tmp_fd, char **cat_line, int *flag)
static int	open_fd_and_calloc(int *tmp_fd, \
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

int	heredoc_child_process(t_info *info, \
	int heredoc_pipe_fd[2], int continue_flag, char *tmp_file)
{
	int		flag;
	int		tmp_fd;
	char	*line;
	char	*cat_line;

	if (open_fd_and_calloc(&tmp_fd, &cat_line, &flag, tmp_file) == ERROR)
		exit(ERROR);
	while (flag == 1)
	{
		flag = get_next_line(0, &line);
		if (flag_check(flag) == ERROR)
			exit(ERROR);
		cat_line = set_cat_line(info->sentence_lst, cat_line, line);
		if (ft_strcmp(line, info->sentence_lst->redirect_lst->str) == 0)
		{
			if (continue_flag == 0)
			{
				if (set_pipe_fd_and_write(heredoc_pipe_fd, tmp_fd, \
					cat_line, line, tmp_file) == ERROR)
					exit(ERROR);
			}
			exit(SUCCESS);
		}
		free(line);
	}
	exit(SUCCESS);
}
