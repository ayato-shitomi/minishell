#include "../includes/minishell.h"

void	free_envp(t_info *info)
{
	size_t	i;

	i = 0;
	while (info->envp[i])
		free(info->envp[i++]);
	free(info->envp);
}
