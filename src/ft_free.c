#include "../includes/minishell.h"

void	ft_free_token_dl_lst(t_info *info)
{
	size_t	i;
	size_t	dl_lstsize;

	if (!(info->token_dl_lst))
		return ;
	i = 0;
	dl_lstsize = ft_dl_lstsize(info->token_dl_lst);
	while (1)
	{
		free(info->token_dl_lst->token);
		info->token_dl_lst = info->token_dl_lst->next;
		if (info->token_dl_lst->dl_lst_first_flag == 1)
		{
			while (i++ < dl_lstsize)
			{
				if (info->token_dl_lst->dl_lst_last_flag == 1)
				{
					free(info->token_dl_lst);
					return ;
				}
				info->token_dl_lst = info->token_dl_lst->next;
				free(info->token_dl_lst->prev);
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
