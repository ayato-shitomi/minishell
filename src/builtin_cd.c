#include "../includes/minishell.h"

int	ft_cd(char *dir)
{
	int	n;

	n = chdir(dir);
	if (n != 0)
		return (1)
	return (0);
}

int	main(void)
{
	char	*path = "/Users/ashitomi";
	char	path_name[200];
	int		n;

	getcwd(path_name, 200);
	printf("before \t: %s\n", path_name);
	n = ft_cd(path);
	if (n != 0)
	{
		printf("error\n");
	}
	getcwd(path_name, 200);
	printf("after \t: %s\n", path_name);
	return (0);
}
