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

static void echo(char *str)
{
	int n;

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

int	ft_echo(t_info *info)
{
	t_lst	*p;
	int		flag_not_backn;
	//int		quote_num;

	//dbg(info);
	flag_not_backn = 0;
	p = info->sentence_lst->cmd_lst->next;
	// quote_num = check_quoted(info);
	if (ft_strncmp(p->str, "-n", ft_strlen(p->str)) == 0)
	{
		flag_not_backn = 1;
		p = p->next;
	}
	while (p)
	{
		// printf("TOKEN > %d\n", p->token_type);
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
