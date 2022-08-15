#include "../includes/minishell.h"

void	set_sentence_lst_and_pipe_fd(t_sentence_lst *sentence_lst, \
	size_t cmd_cnt, int pipe_fd[2], size_t i)
{
	while (i++ < cmd_cnt - 1)
		sentence_lst = sentence_lst->next;
	set_pipe_fd_2(sentence_lst, pipe_fd);
}
