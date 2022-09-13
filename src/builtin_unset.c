/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi <ashitomi@student.42tokyo.jp >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 01:46:26 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/14 01:46:26 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
static void	show_env(t_env_var_lst *a)
{
	t_env_var_lst	*nxt;

	printf("============================================\n");
	nxt = a->next;
	while (nxt)
	{
		printf(" nxt: %p next: %p prev: %p \n \t %s \t %s\n", 
			nxt, nxt->next, nxt->prev, nxt->key, nxt->value);
		nxt = nxt->next;
	}
	printf("============================================\n");
	return ;
}
*/

static int	ft_is_same(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	if (ft_strncmp(s1, s2, ft_strlen(s1)) != 0)
		return (1);
	return (0);
}

static void make_null(t_env_var_lst *nxt)
{
	free(nxt->prev->next->value);
	free(nxt->prev->next->key);
	nxt->prev->next = nxt->next;
}

static void	delete_env(t_env_var_lst *lst, char *key)
{
	t_env_var_lst	*nxt;

	nxt = lst;
	while (nxt)
	{
		if (ft_is_same(nxt->key, key) == 0)
		{
			if (nxt->next != NULL)
			{
				nxt->key = nxt->next->key;
				nxt->value = nxt->next->value;
				nxt->next = nxt->next->next;
				if (nxt->next->next != NULL)
					nxt->next->next->prev = nxt;
			}
			else
				make_null(nxt);
			break ;
		}
		nxt = nxt->next;
	}
	return ;
}

/*
static void	delete_env(t_env_var_lst *lst, char *key)
{
	t_env_var_lst	*nxt;

	nxt = lst;
	while (nxt)
	{
		if (ft_is_same(nxt->key, key) == 0)
		{
			if (nxt->next != NULL)
			{
				nxt->key = nxt->next->key;
				nxt->value = nxt->next->value;
				nxt->next = nxt->next->next;
				if (nxt->next->next != NULL)
					nxt->next->next->prev = nxt;
			}
			else
			{
				free(nxt->prev->next->value);
				free(nxt->prev->next->key);
				nxt->prev->next = nxt->next;
			}
			break ;
		}
		nxt = nxt->next;
	}
	return ;
}
*/

/*
static void	delete_env(t_env_var_lst *lst, char *key)
{
	t_env_var_lst	*nxt;

	nxt = lst;
	while (nxt)
	{
		if (ft_is_same(nxt->key, key) == 0)
		{
			//printf(" %s \t %s\n", nxt->key, nxt->value);
			if (nxt->next != NULL)
			{
				nxt->key = nxt->next->key;
				nxt->value = nxt->next->value;
				nxt->next = nxt->next->next;
			}
			else
			{
				nxt->key = NULL;
				nxt->value = NULL;
				nxt->next = NULL;
			}
		}
		else
			nxt = nxt->next;
	}
	return ;
}
*/

int	ft_unset(t_info *info)
{
	char	*key;

	if (!info->sentence_lst->cmd_lst->next)
		return (0);
	key = info->sentence_lst->cmd_lst->next->str;
	delete_env(info->env_var_lst, key);
	return (0);
}

/*
int	ft_unset(t_info *info)
{

	char	*key;

	if (!info->sentence_lst->cmd_lst->next)
		return (0);
	key = info->sentence_lst->cmd_lst->next->str;
	//printf("DBG > %s\n", key);
	//show_env(info->env_var_lst);
	delete_env(info->env_var_lst, key);
	//show_env(info->env_var_lst);
	return (0);
}
*/
