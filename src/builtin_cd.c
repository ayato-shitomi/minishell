#include "../includes/minishell.h"

int	ft_cd(char *dir)
{
	int		n;
	char	*cwd;

	if (dir == NULL)
	{
		n = chdir(getenv("HOME"));
	}
	else
	{
		n = chdir(dir);
		if (n == 0)
		{
			cwd = ft_strjoin_three(cwd, "/", dir);
		}
		ft_pwd();
	}
	if (n != 0)
		return (ERROR);
	return (SUCCESS);
}

/*
int	main(void)
{
	char	*path = "/Users/ashitomi/Library";
	char	path_name[200];
	int		n;

	getcwd(path_name, 200);
	printf("before \t: %s\n", path_name);
	n = ft_cd(path);
	getcwd(path_name, 200);
	printf("after %d\t: %s\n", n, path_name);

	char	*not_ex_path = "/Unko/Unko/Unko";
	getcwd(path_name, 200);
	printf("before \t: %s\n", path_name);
	n = ft_cd(not_ex_path);
	getcwd(path_name, 200);
	printf("after %d\t: %s\n", n, path_name);

	char	*home = NULL;
	getcwd(path_name, 200);
	printf("before \t: %s\n", path_name);
	n = ft_cd(NULL);
	getcwd(path_name, 200);
	printf("after %d\t: %s\n", n, path_name);
	return (0);
}
*/
