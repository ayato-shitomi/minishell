#include "../includes/minishell.h"

static int	heredoc_parent_process(t_sentence_lst *sentence_lst, \
	int heredoc_pipe_fd[2], int continue_flag)
{
	int		flag;
	int		tmp_fd;
	char	*line;
	char	*concatenated_line;
	char	*concatenated_line_tmp;

	tmp_fd = open("tmp.txt", O_RDWR | O_CREAT, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	concatenated_line = (char *)ft_calloc(1, sizeof(char));
	if (!concatenated_line)
		exit(ERROR);
	flag = 1;
	while (flag == 1)
	{
		flag = get_next_line(0, &line);
		if (flag == -1)
		{
			perror("bash");
			return (ERROR);
		}
		concatenated_line_tmp = concatenated_line;
		if (ft_strncmp(line, sentence_lst->redirect_lst->str, \
			ft_strlen(sentence_lst->redirect_lst->str)) != 0)
		{
			concatenated_line = ft_strjoin_three(concatenated_line, line, "\n");
			free(concatenated_line_tmp);
		}
		if (ft_strncmp(line, sentence_lst->redirect_lst->str, \
			ft_strlen(sentence_lst->redirect_lst->str)) == 0)
		{
			if (continue_flag == 0)
			{
				close(heredoc_pipe_fd[0]);
				dup2(heredoc_pipe_fd[1], tmp_fd);
				close(heredoc_pipe_fd[1]);
				write(tmp_fd, concatenated_line, ft_strlen(concatenated_line));
				close(tmp_fd);
				unlink("tmp.txt");
				free(line);
				free(concatenated_line);
			}
			if (continue_flag == 0)
				exit(SUCCESS);
			return (SUCCESS);
		}
		free(line);
	}
	return (SUCCESS);
}

static void	set_continue_flag(t_sentence_lst *sentence_lst, int *continue_flag)
{
	*continue_flag = 0;
	if (sentence_lst->redirect_lst->next)
		if (sentence_lst->redirect_lst->next->str)
			*continue_flag = 1;
}

int	heredoc(t_sentence_lst *sentence_lst)
{
	int		continue_flag;
	int		heredoc_pipe_fd[2];
	int		heredoc_pid;

	set_continue_flag(sentence_lst, &continue_flag);
	if (pipe(heredoc_pipe_fd) == -1)
	{
		perror("bash");
		return (ERROR);
	}
	heredoc_pid = fork();
	if (heredoc_pid < 0)
		exit(ERROR);
	else if (heredoc_pid == 0)
	{
		set_pipe_fd_0(heredoc_pipe_fd);
		if (continue_flag == 1)
			exit(SUCCESS);
	}
	else
		if (heredoc_parent_process(sentence_lst, heredoc_pipe_fd, \
			continue_flag) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
