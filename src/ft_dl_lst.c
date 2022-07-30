#include "../includes/minishell.h"

size_t	ft_dl_lstsize(t_token_dl_lst *dl_lst)
{
	int	i;

	i = 0;
	if (!dl_lst)
		return (0);
	while (dl_lst->dl_lst_last_flag == 0)
	{
		dl_lst = dl_lst->next;
		i++;
	}
	i++;
	return (i);
}

t_token_dl_lst	*ft_dl_lstfirst(t_token_dl_lst *dl_lst)
{
	if (!dl_lst)
		return (NULL);
	while (dl_lst->dl_lst_first_flag == 0)
		dl_lst = dl_lst->prev;
	return (dl_lst);
}

t_token_dl_lst	*ft_dl_lstlast(t_token_dl_lst *dl_lst)
{
	if (!dl_lst)
		return (NULL);
	while (dl_lst->dl_lst_last_flag == 0)
		dl_lst = dl_lst->next;
	return (dl_lst);
}

void	ft_dl_lstadd_back(t_token_dl_lst **dl_lst, t_token_dl_lst *new)
{
	t_token_dl_lst	*dl_lst_tmp;

	if (!new)
		return ;
	if (!(*dl_lst))
	{
		*dl_lst = new;
		return ;
	}
	else
	{
		dl_lst_tmp = ft_dl_lstlast(*dl_lst);
		(ft_dl_lstlast(*dl_lst))->next = new;
		(ft_dl_lstlast(*dl_lst))->next->dl_lst_last_flag = 1;
		(ft_dl_lstlast(*dl_lst))->dl_lst_last_flag = 0;
		(ft_dl_lstlast(*dl_lst))->prev = dl_lst_tmp;
		(ft_dl_lstlast(*dl_lst))->next = ft_dl_lstfirst(*dl_lst);
		(ft_dl_lstfirst(*dl_lst))->prev = ft_dl_lstlast(*dl_lst);
	}
}

t_token_dl_lst	*ft_dl_lstnew(void *token)
{
	t_token_dl_lst	*new_elem;

	new_elem = (t_token_dl_lst *)ft_calloc(1, sizeof(t_token_dl_lst));
	if (!(new_elem))
		exit(ERROR);
	new_elem->token = token;
	new_elem->prev = new_elem;
	new_elem->next = new_elem;
	new_elem->dl_lst_first_flag = 0;
	new_elem->dl_lst_last_flag = 0;
	return (new_elem);
}
