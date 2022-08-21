#include "../includes/minishell.h"

int	ft_pwd(void)
{
	// char	*cwd;

	// g_builtin_info.cwd = getcwd(NULL, 0);
	// if (!cwd)
	// 	exit (1);
	printf("pwd = %s\n", g_builtin_info.cwd);
	// free(cwd);
	exit (0);
}

/*
int main(void)
{
	ft_pwd();
}
*/
