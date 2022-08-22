#include "../includes/minishell.h"

int	error_and_return(char *cmd, char *arg, char *err_msg)
{
	ft_putstr_fd(SHELLNAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (err_msg)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	return (ERROR);
}

void	error_and_exit(char *error_str_1, char *error_str_2, int exit_status)
{
	ft_putstr_fd(SHELLNAME, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (error_str_1)
	{
		ft_putstr_fd(error_str_1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error_str_2)
		ft_putendl_fd(error_str_2, STDERR_FILENO);
	exit(exit_status);
}
