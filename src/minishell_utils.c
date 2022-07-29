#include "../includes/minishell.h"

void	set_token_type(char *token, t_token_lst *token_lst)
{
	size_t	len;

	len = ft_strlen(token);
	if (ft_strncmp(token, "|", 1) == 0)
		token_lst->type = PIPE;
	else if (ft_strncmp(token, "<", 1) == 0)
	{
		if (len >= 2)
		{
			if (token[1] == '<')
				token_lst->type = REDIRECT_LEFT_TWO;
			else
				token_lst->type = REDIRECT_LEFT_ONE;
		}
		else
			token_lst->type = REDIRECT_LEFT_ONE;
	}
	else if (ft_strncmp(token, ">", 1) == 0)
	{
		if (len >= 2)
		{
			if (token[1] == '>')
				token_lst->type = REDIRECT_RIGHT_TWO;
			else
				token_lst->type = REDIRECT_RIGHT_ONE;
		}
		else
			token_lst->type = REDIRECT_RIGHT_ONE;
	}
	// else if ((ft_strncmp(token, ">", 1) == 0) || \
	// 	(ft_strncmp(token, "<", 1) == 0) || (ft_strncmp(token, ">>", 2) == 0) || \
	// 	(ft_strncmp(token, "<<", 2) == 0))
	// 	token_lst->type = REDIRECT;
	else
	{
		if (ft_strncmp(token, "\"", 1) == 0)
			token_lst->type = EXPANDABLE_QUOTED;
		else if (ft_strncmp(token, "\'", 1) == 0)
			token_lst->type = NOT_EXPANDABLE;
		else
			token_lst->type = EXPANDABLE;
	}
}

void	init_quote_flag(t_info *info)
{
	info->is_in_dquote = 0;
	info->is_in_squote = 0;
}

void	quote_check(char c, t_info *info)
{
	if (c == '\"' && info->is_in_dquote == 0)
		info->is_in_dquote = 1;
	else if (c == '\"' && info->is_in_dquote == 1)
		info->is_in_dquote = 0;
	else if (c == '\'' && info->is_in_squote == 0)
		info->is_in_squote = 1;
	else if (c == '\'' && info->is_in_squote == 1)
		info->is_in_squote = 0;
}
