#include "../includes/minishell.h"

static void	create_lstnew(t_info *info, size_t *i)
{
	info->token_lst = ft_lstnew_ms(info->split_command[*i]);
	info->token_lst->lst_first_flag = 1;
	info->token_lst->lst_last_flag = 1;
	set_token_type(info->split_command[*i], info->token_lst);
}

int	lexical_analysis(t_info *info)
{
	//字句解析用関数
	size_t		i;
	t_token_lst	*lst_tmp;

	info->split_command = ft_split_ms(info->parsed_command, info);
	if (!(info->split_command))
		exit(ERROR);
	free(info->parsed_command);
	i = 0;
	create_lstnew(info, &i);
	i++;
	while (info->split_command[i])
	{
		lst_tmp = ft_lstnew_ms(info->split_command[i]);
		ft_lstadd_back_ms(&(info->token_lst), lst_tmp);
		set_token_type(info->split_command[i], ft_lstlast_ms(info->token_lst));
		i++;
	}
	lexical_analysis_2(info);
	return (SUCCESS);
}
