/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashitomi </var/mail/ashitomi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:17:50 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/11 13:18:47 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	put_std_err(char *str)
{
	int	n;

	n = ft_strlen(str);
	write(2, str, n);
	return ;
}

static int	make_status(char *str)
{
	int	n;

	if (!(ft_strcmp(str, "-9223372036854775809")))
		return (255);
	n = ft_atoi((const char *)str);
	if (n == 0)
		return (0);
	return (n % 256);
}

static int	check_arg(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (!('0' <= str[n] && str[n] <= '9'))
			return (1);
		n++;
	}
	return (0);
}

void	case_in_numeric_arg(char *arg)
{
	char	*s;

	s = "numeric argument required";
	put_std_err(SHELLNAME);
	put_std_err(": exit: ");
	put_std_err(arg);
	put_std_err(": ");
	put_std_err(s);
	put_std_err("\n");
}

int	ft_exit(size_t ac, char **cmd, t_lst *cmd_lst)
{
	char	*arg;

	put_std_err("exit\n");
	if (ac == 1)
		exit (0);
	if (cmd_lst == NULL)
		arg = cmd[1];
	else
		arg = cmd_lst->next->str;
	if (check_arg(arg))
	{
		case_in_numeric_arg(arg);
		exit(255);
	}
	if (3 <= ac)
	{
		put_std_err(SHELLNAME);
		put_std_err(": exit: too many arguments\n");
		return (1);
	}
	exit(make_status(arg));
	return (1);
}
