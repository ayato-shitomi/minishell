#include "../includes/minishell.h"

t_lst	*ft_lstlast(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	else
		(ft_lstlast(*lst))->next = new;
}

t_lst	*ft_lstnew(void *content)
{
	t_lst	*new_elem;

	new_elem = (t_lst *)ft_calloc(1, sizeof(t_lst));
	if (!new_elem)
		exit (ERROR);
	new_elem->str = content;
	new_elem->key = NULL;
	new_elem->value = NULL;
	new_elem->next = NULL;
	return (new_elem);
}