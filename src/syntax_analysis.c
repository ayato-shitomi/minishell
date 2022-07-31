#include "../includes/minishell.h"

static void	set_lst_info(t_info *info, t_lst *lst, int flag)
{
	if (flag == REDIRECT_LST)
		lst->lst_type = REDIRECT_LST;
	else if (flag == CMD_LST)
		lst->lst_type = CMD_LST;
	else if (flag == ENV_VAR_LST)
		lst->lst_type = ENV_VAR_LST;
	if (flag == REDIRECT_LST || flag == CMD_LST)
		lst->token_type = info->token_dl_lst->type;
	else if (flag == ENV_VAR_LST)
		lst->token_type = ENVIRONMENT_VAR;
}

static void	check_env_var_and_set_env_var_info(t_info *info, t_lst *lst)
{
	size_t	i;
	size_t	j;
	size_t	i_tmp;
	size_t	len;
	t_lst	*env_var_lst;

	i = 0;
	len = 0;
	if (lst->token_type == NOT_EXPANDABLE)
		return ;
	else
	{
		while (lst->str[i])
		{
			if (lst->str[i] == '$')
			{
				env_var_lst = ft_lstnew(NULL);
				set_lst_info(info, env_var_lst, ENV_VAR_LST);
				i++;
				i_tmp = i;
				while (lst->str[i] != '\"' && lst->str[i] != ' ' && \
					lst->str[i] != '?' && lst->str[i] != '\0')
				{
					len++;
					i++;
				}
				i = i_tmp;
				env_var_lst->key = (char *)ft_calloc(len + 1, sizeof(char));
				if (!(env_var_lst->key))
					exit(ERROR);
				j = 0;
				while (j < len)
				{
					env_var_lst->key[j] = lst->str[i];
					i++;
					j++;
				}
				env_var_lst->key[j] = '\0';
				env_var_lst->value = getenv(env_var_lst->key);
				ft_lstadd_back(&(info->sentence_lst->env_var_lst), env_var_lst);
			}
			i++;
		}
	}
}

static void	set_lst_of_sentence_lst(t_info *info)
{
	int				flag;
	t_sentence_lst	*sentence_lst_tmp;
	t_lst			*lst;

	sentence_lst_tmp = info->sentence_lst;
	while (info->sentence_lst)
	{
		flag = CMD_LST;
		while (1)
		{
			if (info->token_dl_lst->type == PIPE)
			{
				info->token_dl_lst = info->token_dl_lst->next;
				break ;
			}
			else if ((info->token_dl_lst->type >= REDIRECT_LEFT_ONE && \
				info->token_dl_lst->type <= REDIRECT_RIGHT_TWO) || \
				flag == REDIRECT_LST)
			{
				flag = REDIRECT_LST;
				lst = ft_lstnew(info->token_dl_lst->token);
				set_lst_info(info, lst, flag);
				check_env_var_and_set_env_var_info(info, lst);
				ft_lstadd_back(&(info->sentence_lst->redirect_lst), lst);
			}
			else
			{
				flag = CMD_LST;
				lst = ft_lstnew(info->token_dl_lst->token);
				set_lst_info(info, lst, flag);
				check_env_var_and_set_env_var_info(info, lst);
				ft_lstadd_back(&(info->sentence_lst->cmd_lst), lst);
			}
			info->token_dl_lst = info->token_dl_lst->next;
			if (info->token_dl_lst->dl_lst_first_flag == 1)
				break ;
		}
		if (info->token_dl_lst->dl_lst_first_flag == 1)
			break ;
		info->sentence_lst = info->sentence_lst->next;
	}
	info->sentence_lst = sentence_lst_tmp;
}

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
