#include "../includes/minishell.h"

static void	space_check_and_set_char(char *command, t_info *info, \
	size_t i, size_t *j)
{
	if (info->is_in_dquote == 1 || info->is_in_squote == 1)
	{
		info->parsed_command[*j] = command[i];
		*j += 1;
		info->space_cnt = 0;
	}
	else if (command[i] != ' ' && \
		(info->is_in_dquote == 0 && info->is_in_squote == 0))
	{
		info->parsed_command[*j] = command[i];
		*j += 1;
		info->space_cnt = 0;
	}
	else
	{
		info->space_cnt++;
	}
	if (info->space_cnt == 1)
	{
		info->parsed_command[*j] = command[i];
		*j += 1;
	}
}

void	remove_space(char *command, t_info *info)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(command);
	info->parsed_command = ft_calloc(len + 1, sizeof(char));
	if (!info->parsed_command)
		exit(ERROR);
	while (command[i])
	{
		quote_check(command[i], info);
		space_check_and_set_char(command, info, i, &j);
		i++;
	}
	init_quote_flag(info);
}
