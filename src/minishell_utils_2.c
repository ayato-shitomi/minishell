#include "../includes/minishell.h"

int	set_exit_status(t_info *info, int exit_status)
{
	info->exit_status = exit_status;
	return (exit_status);
}
