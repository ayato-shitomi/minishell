/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:36:02 by mhida             #+#    #+#             */
/*   Updated: 2022/07/22 13:38:25 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_split_command(char **split_command)
{
	size_t	i;

	i = 0;
	while (split_command[i])
		free(split_command[i++]);
	free(split_command);
}
