#include "../includes/minishell.h"

static void	set_pipe_fd_and_write(int heredoc_pipe_fd[2], int tmp_fd, \
	char *cat_line, char *line)
{
	close(heredoc_pipe_fd[0]);
	dup2(heredoc_pipe_fd[1], tmp_fd);
	close(heredoc_pipe_fd[1]);
	write(tmp_fd, cat_line, ft_strlen(cat_line));
	close(tmp_fd);
	if (unlink("tmp.txt") == -1)
	{
		perror(SHELLNAME);
		exit(ERROR);
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
	if (ft_strncmp(line, sentence_lst->redirect_lst->str, \
		ft_strlen(sentence_lst->redirect_lst->str)) != 0)
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

static int	open_fd_and_calloc(int *tmp_fd, char **cat_line, int *flag)
{
	*tmp_fd = open("tmp.txt", O_RDWR | O_CREAT, \
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

int	heredoc_parent_process(t_info *info, int heredoc_pipe_fd[2], \
	int continue_flag)
{
	int		flag;
	int		tmp_fd;
	char	*line;
	char	*cat_line;

	if (open_fd_and_calloc(&tmp_fd, &cat_line, &flag) == ERROR)
		return (ERROR);
	while (flag == 1)
	{
		write(2, "check_2\n", 8);
		// init_and_set_fd_for_restore(info, 0);
		flag = get_next_line(0, &line);
		// init_and_set_fd_for_restore(info, 2);
		if (flag_check(flag) == ERROR)
			return (ERROR);
		write(2, "check_3\n", 8);
		cat_line = set_cat_line(info->sentence_lst, cat_line, line);
		if (ft_strncmp(line, info->sentence_lst->redirect_lst->str, \
			ft_strlen(info->sentence_lst->redirect_lst->str)) == 0)
		{
			if (continue_flag == 0)
				set_pipe_fd_and_write(heredoc_pipe_fd, tmp_fd, \
					cat_line, line);
			return (SUCCESS);
		}
		free(line);
	}
	return (SUCCESS);
}
