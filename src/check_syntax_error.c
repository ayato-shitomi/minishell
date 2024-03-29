/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/17 22:30:54 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_syntax_error_5(char *err_str)
{
	char	*err_message;

	err_message = ft_strjoin("Fresh: syntax error near unexpected token ", \
		err_str);
	free(err_str);
	ft_putendl_fd(err_message, STDERR_FILENO);
	free(err_message);
	return (ERROR);
}

static void	check_syntax_error_4(t_sentence_lst *sentence_lst, char **err_str)
{
	if ((sentence_lst->redirect_lst->token_type >= REDIRECT_LEFT_ONE && \
	sentence_lst->redirect_lst->token_type <= REDIRECT_RIGHT_TWO) && \
	((sentence_lst->redirect_lst->next->token_type >= \
	REDIRECT_LEFT_ONE && \
	sentence_lst->redirect_lst->next->token_type <= \
	REDIRECT_RIGHT_TWO)))
	{
		*err_str = ft_strjoin_three("`", \
			sentence_lst->redirect_lst->next->str, "\'");
	}
}

static int	check_syntax_error_3(t_sentence_lst *sentence_lst)
{
	char	*err_str;
	t_lst	*redirect_lst_tmp;

	redirect_lst_tmp = sentence_lst->redirect_lst;
	while (sentence_lst->redirect_lst)
	{
		err_str = NULL;
		if (sentence_lst->redirect_lst->next)
			check_syntax_error_4(sentence_lst, &err_str);
		else if ((sentence_lst->redirect_lst->token_type >= REDIRECT_LEFT_ONE \
			&& sentence_lst->redirect_lst->token_type <= REDIRECT_RIGHT_TWO) \
			&& (!(sentence_lst->redirect_lst->next) && sentence_lst->next))
				err_str = ft_strjoin_three("`", "|", "\'");
		else if ((sentence_lst->redirect_lst->token_type >= REDIRECT_LEFT_ONE \
			&& sentence_lst->redirect_lst->token_type <= REDIRECT_RIGHT_TWO) \
			&& (!(sentence_lst->redirect_lst->next) && !(sentence_lst->next)))
			err_str = ft_strjoin_three("`", "newline", "\'");
		if (err_str)
			return (check_syntax_error_5(err_str));
		sentence_lst->redirect_lst = sentence_lst->redirect_lst->next;
	}
	sentence_lst->redirect_lst = redirect_lst_tmp;
	return (SUCCESS);
}

static int	check_syntax_error_2(t_sentence_lst *sentence_lst)
{
	char	*err_message;
	char	*err_str;

	if (!sentence_lst->cmd_lst && !sentence_lst->redirect_lst && \
		sentence_lst->next)
	{
		err_str = ft_strjoin_three("`", "|", "\'");
		err_message = \
		ft_strjoin("Fresh: syntax error near unexpected token ", \
			err_str);
		free(err_str);
		ft_putendl_fd(err_message, STDERR_FILENO);
		free(err_message);
		return (ERROR);
	}
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
