/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:20:54 by mhida             #+#    #+#             */
/*   Updated: 2022/07/22 11:55:44 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_command(char *command, t_info *info)
{
	if (remove_space(command, info) == ERROR)
		return (ERROR);
	// printf("parsed = %s\n", info->parsed_command);
	if (lexical_analysis(command, info) == ERROR)
		return (ERROR);
	if (syntax_analysis(command, info) == ERROR)
		return (ERROR);
	if (expansion(command, info) == ERROR)
		return (ERROR);
	if (execute_command(command, info) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
