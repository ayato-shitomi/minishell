#include "../includes/minishell.h"

static int	set_fd_case_file(t_sentence_lst *sentence_lst, int prev_token_type)
{
	if (prev_token_type == REDIRECT_LEFT_ONE)
	{
		if (set_fd_case_red_left_one(sentence_lst) == ERROR)
			return (ERROR);
	}
	else if (prev_token_type == REDIRECT_RIGHT_ONE)
	{
		if (set_fd_case_red_right_one(sentence_lst) == ERROR)
			return (ERROR);
	}
	else if (prev_token_type == REDIRECT_LEFT_TWO)
	{
		if (heredoc(sentence_lst) == ERROR)
			return (ERROR);
		return (SUCCESS);
	}
	else if (prev_token_type == REDIRECT_RIGHT_TWO)
	{
		if (set_fd_case_red_right_two(sentence_lst) == ERROR)
			return (ERROR);
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
