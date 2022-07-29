#include "../includes/minishell.h"

void	ft_free_token_lst(t_info *info)
{
	size_t	i;

	i = 0;
	while (1)
	{
		free(info->token_lst->token);
		info->token_lst = info->token_lst->next;
		if (info->token_lst->lst_first_flag == 1)
			break ;
	}
}

// void	ft_free_split_command(char **split_command)
// {
// 	size_t	i;

// 	i = 0;
// 	while (split_command[i])
// 		free(split_command[i++]);
// 	free(split_command);
// }
