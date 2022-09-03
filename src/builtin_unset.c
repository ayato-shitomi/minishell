#include "../includes/minishell.h"

/*
static void	show_env(t_env_var_lst *a)
{
	t_env_var_lst	*nxt;

	printf("============================================\n");
	nxt = a->next;
	while (nxt)
	{
		printf(" %s \t %s\n", nxt->key, nxt->value);
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

static void	delete_env(t_env_var_lst *lst, char *key)
{
	t_env_var_lst	*nxt;

	nxt = lst->next;
	while (nxt)
	{
		if (ft_is_same(nxt->key, key) == 0)
		{
			printf(" %s \t %s\n", nxt->key, nxt->value);
			if (nxt->next != NULL)
			{
				nxt->key = nxt->next->key;
				nxt->value = nxt->next->value;
				nxt->next = nxt->next->next;
			}
			else
				nxt = NULL;
		}
		else
			nxt = nxt->next;
	}
	return ;
}

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
