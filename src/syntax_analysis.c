/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:55:29 by mhida             #+#    #+#             */
/*   Updated: 2022/07/22 11:55:51 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_analysis(char *command, t_info *info)
{
	//構文解析用関数
	if (!command && !info) //コンパイル時のunused対策
		return (ERROR);
	return (SUCCESS);
}
