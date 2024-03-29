/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:20:14 by ashitomi          #+#    #+#             */
/*   Updated: 2022/09/26 19:59:20 by ashitomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	ft_put_esc(char c)
{
	if (c == '\a')
		return ('a');
	if (c == '\b')
		return ('b');
	if (c == '\t')
		return ('t');
	if (c == '\n')
		return ('n');
	if (c == '\v')
		return ('v');
	if (c == '\f')
		return ('f');
	if (c == '\r')
		return ('r');
	return (0);
}

static void	echo(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (7 <= str[n] && str[n] <= 13)
			printf("%c", (char)ft_put_esc(str[n]));
		printf("%c", str[n]);
		n++;
	}
	return ;
}

//static int	check_quoted(t_info *info);

/*
static void	dbg(t_info *info)
{
	printf("parsed_command\t>> %s\n", info->parsed_command);
	printf("is_in_dquote\t>> %zu\n", info->is_in_dquote);
	printf("is_in_squote\t>> %zu\n", info->is_in_squote);
	//printf("check_quoted\t>> %d\n", check_quoted(info));
}
*/

/*
	ASCII CODE
	34 => "
	39 => '
*/

/*
static int check_quoted(t_info *info)
{
	t_lst	*p;
	int	n;
	int	m;

	n = 0;
	p = info->sentence_lst->cmd_lst->next;
	while (p)
	{
		m = 0;
		printf(">> %s\n", p->str);
		while (p->str[m])
		{
			if ((int)p->str[m] == 34)
				n++;
			m++;
		}
		p = p->next;
	}
	return (n);
}
*/

static int	pbarz(void)
{
	printf("\n");
	return (0);
}

int	ft_echo(t_info *info)
{
	t_lst	*p;
	int		flag_not_backn;

	if (!info->sentence_lst->cmd_lst->next)
		return (pbarz());
	flag_not_backn = 0;
	p = info->sentence_lst->cmd_lst->next;
	while (ft_strcmp(p->str, "-n") == 0)
	{
		flag_not_backn = 1;
		p = p->next;
		if (p == NULL)
			return (0);
	}
	while (p)
	{
		echo(p->str);
		p = p->next;
		if (p)
			printf(" ");
	}
	if (!flag_not_backn)
		printf("\n");
	return (0);
}

/*
int	main(void)
{
	printf("\necho hello\n");
	ft_echo("hello", false);
	printf("\necho -n hello\n");
	ft_echo("hello", true);
	printf("\necho hello\\n\n");
	ft_echo("hello\n", false);
	return (0);
}
*/
