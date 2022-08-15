#include "../includes/minishell.h"

static int	set_fd_case_file(t_sentence_lst *sentence_lst, int prev_token_type)
{
	int	fd_in;
	int	fd_out;

	if (!sentence_lst)
		return (ERROR);
	if (prev_token_type == REDIRECT_LEFT_ONE) // case 「<」
	{
		if (access(sentence_lst->redirect_lst->str, F_OK) == 0)
		{
			if (access(sentence_lst->redirect_lst->str, R_OK) == -1)
				return (ERROR);
		}
		else
		{
			printf("エラー処理書く\n");
			return (ERROR);
		}
		fd_in = open(sentence_lst->redirect_lst->str, O_RDONLY);
		if (fd_in == -1)
			return (ERROR);
		dup2(fd_in, 0);
		close(fd_in);
	}
	else if (prev_token_type == REDIRECT_RIGHT_ONE) // case 「>」
	{
		if (access(sentence_lst->redirect_lst->str, F_OK) == 0)
		{
			if (access(sentence_lst->redirect_lst->str, W_OK) == -1)
				return (ERROR);
		}
		if (access(sentence_lst->redirect_lst->str, F_OK) == 0)
			unlink(sentence_lst->redirect_lst->str);
		fd_out = open(sentence_lst->redirect_lst->str, O_WRONLY | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd_out == -1)
			return (ERROR);
		dup2(fd_out, 1);
		close(fd_out);
	}
	else if (prev_token_type == REDIRECT_LEFT_TWO) // case 「<<」
	{
		if (heredoc(sentence_lst) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	else if (prev_token_type == REDIRECT_RIGHT_TWO) // case 「>>」
	{
		if (access(sentence_lst->redirect_lst->str, F_OK) == 0)
		{
			if (access(sentence_lst->redirect_lst->str, W_OK) == -1)
				return (ERROR);
		}
		fd_out = open(sentence_lst->redirect_lst->str, O_WRONLY | O_APPEND | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd_out == -1)
			return (ERROR);
		dup2(fd_out, 1);
		close(fd_out);
	}
	return (SUCCESS);
}

static int	set_fd_case_redirect(t_sentence_lst *sentence_lst, \
	int prev_token_type)
{
	if (sentence_lst->redirect_lst->token_type == REDIRECT_LEFT_ONE)
		prev_token_type = REDIRECT_LEFT_ONE;
	else if (sentence_lst->redirect_lst->token_type == REDIRECT_RIGHT_ONE)
		prev_token_type = REDIRECT_RIGHT_ONE;
	else if (sentence_lst->redirect_lst->token_type == REDIRECT_LEFT_TWO)
		prev_token_type = REDIRECT_LEFT_TWO;
	else if (sentence_lst->redirect_lst->token_type == REDIRECT_RIGHT_TWO)
		prev_token_type = REDIRECT_RIGHT_TWO;
	return (prev_token_type);
}

static int	case_branch_by_redirect_lst(t_sentence_lst *sentence_lst, \
	int prev_token_type)
{
	if (sentence_lst->redirect_lst->token_type >= REDIRECT_LEFT_ONE && \
		sentence_lst->redirect_lst->token_type <= REDIRECT_RIGHT_TWO)
		prev_token_type = set_fd_case_redirect(sentence_lst, prev_token_type);
	else
		if (set_fd_case_file(sentence_lst, prev_token_type) == ERROR)
			return (ERROR);
	return (prev_token_type);
}

int	set_fd_by_redirect_lst(t_sentence_lst *sentence_lst)
{
	int		prev_token_type;
	t_lst	*redirect_lst_tmp;

	prev_token_type = 0;
	redirect_lst_tmp = sentence_lst->redirect_lst;
	while (sentence_lst->redirect_lst)
	{
		prev_token_type = case_branch_by_redirect_lst(sentence_lst, \
			prev_token_type);
		if (prev_token_type == ERROR)
			return (ERROR);
		sentence_lst->redirect_lst = sentence_lst->redirect_lst->next;
	}
	sentence_lst->redirect_lst = redirect_lst_tmp;
	return (SUCCESS);
}
