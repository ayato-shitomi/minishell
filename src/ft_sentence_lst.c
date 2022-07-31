#include "../includes/minishell.h"

t_sentence_lst	*ft_sentence_lstlast(t_sentence_lst *sentence_lst)
{
	if (!sentence_lst)
		return (NULL);
	while (sentence_lst->next != NULL)
		sentence_lst = sentence_lst->next;
	return (sentence_lst);
}

void	ft_sentence_lstadd_back(t_sentence_lst **sentence_lst, \
	t_sentence_lst *new)
{
	if (!new)
		return ;
	if (!(*sentence_lst))
	{
		*sentence_lst = new;
		return ;
	}
	else
		(ft_sentence_lstlast(*sentence_lst))->next = new;
}

t_sentence_lst	*ft_sentence_lstnew(void)
{
	t_sentence_lst	*new_elem;

	new_elem = (t_sentence_lst *)ft_calloc(1, sizeof(t_sentence_lst));
	if (!new_elem)
		exit(ERROR);
	new_elem->cmd_lst = NULL;
	new_elem->redirect_lst = NULL;
	new_elem->env_var_lst = NULL;
	new_elem->next = NULL;
	return (new_elem);
}
