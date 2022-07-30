#include "../includes/minishell.h"

void	ft_free_token_lst(t_info *info)
{
	size_t	i;
	size_t	lstsize;

	if (!(info->token_lst))
		return ;
	i = 0;
	lstsize = ft_lstsize_ms(info->token_lst);
	while (1)
	{
		free(info->token_lst->token);
		info->token_lst = info->token_lst->next;
		if (info->token_lst->lst_first_flag == 1)
		{
			while (i++ < lstsize)
			{
				if (info->token_lst->lst_last_flag == 1)
				{
					free(info->token_lst);
					return ;
				}
				info->token_lst = info->token_lst->next;
				free(info->token_lst->prev);
			}
		}
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
