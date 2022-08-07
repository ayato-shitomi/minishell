#include "../includes/minishell.h"

void	set_fd_by_redirect_lst(t_info *info, char **cmd)
{
	t_lst	*redirect_lst_tmp;

	redirect_lst_tmp = info->sentence_lst->redirect_lst;
	while (info->sentence_lst->redirect_lst)
	{
		if (cmd) // unused対策
			return ;
		info->sentence_lst->redirect_lst = \
			info->sentence_lst->redirect_lst->next;
	}
	info->sentence_lst->redirect_lst = redirect_lst_tmp;
}
