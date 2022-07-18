/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:56:57 by mhida             #+#    #+#             */
/*   Updated: 2022/07/18 10:05:11 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_command(char *command, t_info *info)
{
	//コマンド実行用関数
	if (!command && !info) //コンパイル時のunused対策
		return (ERROR);
	return (SUCCESS);
}
