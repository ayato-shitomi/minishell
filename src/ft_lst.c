#include "../includes/minishell.h"

size_t	ft_lstsize_ms(t_token_lst *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst->lst_last_flag == 0)
	{
		lst = lst->next;
		i++;
	}
	i++;
	return (i);
}

t_token_lst	*ft_lstfirst_ms(t_token_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->lst_first_flag == 0)
		lst = lst->prev;
	return (lst);
}

t_token_lst	*ft_lstlast_ms(t_token_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->lst_last_flag == 0)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_ms(t_token_lst **lst, t_token_lst *new)
{
	t_token_lst	*lst_tmp;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		lst_tmp = ft_lstlast_ms(*lst);
		(ft_lstlast_ms(*lst))->next = new;
		(ft_lstlast_ms(*lst))->next->lst_last_flag = 1;
		(ft_lstlast_ms(*lst))->lst_last_flag = 0;
		(ft_lstlast_ms(*lst))->prev = lst_tmp;
		(ft_lstlast_ms(*lst))->next = ft_lstfirst_ms(*lst);
		(ft_lstfirst_ms(*lst))->prev = ft_lstlast_ms(*lst);
	}
}

t_token_lst	*ft_lstnew_ms(void *token)
{
	t_token_lst	*new_elem;

	new_elem = (t_token_lst *)ft_calloc(1, sizeof(t_token_lst));
	if (!(new_elem))
		exit(ERROR);
	new_elem->token = token;
	new_elem->prev = new_elem;
	new_elem->next = new_elem;
	new_elem->lst_first_flag = 0;
	new_elem->lst_last_flag = 0;
	return (new_elem);
}
