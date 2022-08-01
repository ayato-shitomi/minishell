#include "../includes/minishell.h"

static void	create_sentence_lst(t_info *info)
{
	size_t			i;
	size_t			pipe_cnt;
	t_sentence_lst	*sentence_lst;

	pipe_cnt = 0;
	while (1)
	{
		if (info->token_dl_lst->type == PIPE)
			pipe_cnt++;
		info->token_dl_lst = info->token_dl_lst->next;
		if (info->token_dl_lst->dl_lst_first_flag == 1)
			break ;
	}
	info->sentence_lst = ft_sentence_lstnew();
	i = 0;
	while (i < pipe_cnt)
	{
		sentence_lst = ft_sentence_lstnew();
		ft_sentence_lstadd_back(&(info->sentence_lst), sentence_lst);
		i++;
	}
}

int	syntax_analysis(t_info *info)
{
	//構文解析用関数
	create_sentence_lst(info);
	set_lst_of_sentence_lst(info);
	return (SUCCESS);
}
