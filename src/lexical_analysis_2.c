#include "../includes/minishell.h"

void	lexical_analysis_2(t_info *info)
{
	size_t	i;
	int		flag;

	while (1)
	{
		i = 0;
		flag = 0;
		while (info->token_lst->token[i] && flag == 0)
		{
			if (info->token_lst->token[i] == '\"')
				flag = split_token_for_dquote(info, &i);
			else if (info->token_lst->token[i] == '\'')
				flag = split_token_for_squote(info, &i);
			else if (info->token_lst->token[i] == '|')
				flag = split_token_for_pipe(info, &i);
			else if (info->token_lst->token[i] == '>' || \
				info->token_lst->token[i] == '<')
				flag = split_token_for_redirect(info, &i);
			i++;
		}
		info->token_lst = info->token_lst->next;
		if (info->token_lst->lst_first_flag == 1)
			break ;
	}
}
