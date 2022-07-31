#include "../includes/minishell.h"

static void	set_token_type_dl_4(char *token, t_token_dl_lst *token_dl_lst)
{
	if (ft_strncmp(token, "\"", 1) == 0)
		token_dl_lst->type = EXPANDABLE_QUOTED;
	else if (ft_strncmp(token, "\'", 1) == 0)
		token_dl_lst->type = NOT_EXPANDABLE;
	else
		token_dl_lst->type = EXPANDABLE;
}

static void	set_token_type_dl_3(char *token, t_token_dl_lst *token_dl_lst, \
	size_t len)
{
	if (len >= 2)
	{
		if (token[1] == '>')
			token_dl_lst->type = REDIRECT_RIGHT_TWO;
		else
			token_dl_lst->type = REDIRECT_RIGHT_ONE;
	}
	else
		token_dl_lst->type = REDIRECT_RIGHT_ONE;
}

static void	set_token_type_dl_2(char *token, t_token_dl_lst *token_dl_lst, \
	size_t len)
{
	if (len >= 2)
	{
		if (token[1] == '<')
			token_dl_lst->type = REDIRECT_LEFT_TWO;
		else
			token_dl_lst->type = REDIRECT_LEFT_ONE;
	}
	else
		token_dl_lst->type = REDIRECT_LEFT_ONE;
}

void	set_token_type_dl(char *token, t_token_dl_lst *token_dl_lst)
{
	size_t	len;

	len = ft_strlen(token);
	if (ft_strncmp(token, "|", 1) == 0)
		token_dl_lst->type = PIPE;
	else if (ft_strncmp(token, "<", 1) == 0)
		set_token_type_dl_2(token, token_dl_lst, len);
	else if (ft_strncmp(token, ">", 1) == 0)
		set_token_type_dl_3(token, token_dl_lst, len);
	else
		set_token_type_dl_4(token, token_dl_lst);
}
