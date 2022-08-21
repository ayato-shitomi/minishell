#include "../includes/minishell.h"

//#include <stdio.h>

/*
   if flag_n == false
   do echo with -n
   if flag_esc == true
   do echo with -e
*/

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
	char	*c;

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

int	ft_echo(char *str, bool flag_n)
{
	echo(str);
	if (flag_n == false)
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
