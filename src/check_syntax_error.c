#include "../includes/minishell.h"

static int	check_syntax_error_2(t_sentence_lst *sentence_lst)
{
	char	*err_message;
	char	*err_str;

	if (!sentence_lst->cmd_lst && !sentence_lst->redirect_lst && \
		sentence_lst->next)
	{
		err_str = ft_strjoin_three("`", "|", "\'");
		err_message = \
		ft_strjoin("bash: syntax error near unexpected token ", \
		err_str);
		free(err_str);
		ft_putendl_fd(err_message, STDERR_FILENO);
		free(err_message);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	check_syntax_error_3(t_sentence_lst *sentence_lst)
{
	char	*err_message;
	char	*err_str;
	t_lst	*redirect_lst_tmp;

	redirect_lst_tmp = sentence_lst->redirect_lst;
	while (sentence_lst->redirect_lst)
	{
		err_str = NULL;
		if (sentence_lst->redirect_lst->next)
		{
			if ((sentence_lst->redirect_lst->token_type >= REDIRECT_LEFT_ONE && \
			sentence_lst->redirect_lst->token_type <= REDIRECT_RIGHT_TWO) && \
			((sentence_lst->redirect_lst->next->token_type >= \
			REDIRECT_LEFT_ONE && \
			sentence_lst->redirect_lst->next->token_type <= \
			REDIRECT_LEFT_TWO)))
			{
				err_str = ft_strjoin_three("`", \
					sentence_lst->redirect_lst->next->str, "\'");
			}
		}
		else
		{
			if ((sentence_lst->redirect_lst->token_type >= REDIRECT_LEFT_ONE && \
			sentence_lst->redirect_lst->token_type <= REDIRECT_RIGHT_TWO) && \
			(!(sentence_lst->redirect_lst->next) && sentence_lst->next))
			{
				err_str = ft_strjoin_three("`", "|", "\'");
			}
		}
		if (err_str)
		{
			err_message = \
			ft_strjoin("bash: syntax error near unexpected token ", \
			err_str);
			free(err_str);
			ft_putendl_fd(err_message, STDERR_FILENO);
			free(err_message);
			return (ERROR);
		}
		sentence_lst->redirect_lst = sentence_lst->redirect_lst->next;
	}
	sentence_lst->redirect_lst = redirect_lst_tmp;
	return (SUCCESS);
}

int	check_syntax_error(t_info *info)
{
	t_sentence_lst	*sentence_lst_tmp;

	sentence_lst_tmp = info->sentence_lst;
	while (info->sentence_lst)
	{
		if (check_syntax_error_2(info->sentence_lst) == ERROR)
			return (ERROR);
		if (check_syntax_error_3(info->sentence_lst) == ERROR)
			return (ERROR);
		info->sentence_lst = info->sentence_lst->next;
	}
	info->sentence_lst = sentence_lst_tmp;
	return (SUCCESS);
}
