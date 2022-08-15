#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit (1);
	printf("%s\n", cwd);
	free(cwd);
	exit (0);
}

/*
int main(void)
{
	ft_pwd();
}
*/
