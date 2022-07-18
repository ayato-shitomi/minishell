/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:57:55 by mhida             #+#    #+#             */
/*   Updated: 2022/07/18 10:05:15 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expansion(char *command, t_info *info)
{
	//変数展開用関数
	if (!command && !info) //コンパイル時のunused対策
		return (ERROR);
	return (SUCCESS);
}
