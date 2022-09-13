/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:27 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:27 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_lstsize(t_lst *lst)
{
	size_t	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		i++;
	}
	i++;
	return (i);
}

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
	new_elem->str = ft_strdup(content);
	new_elem->key = NULL;
	new_elem->value = NULL;
	new_elem->next = NULL;
	return (new_elem);
}
