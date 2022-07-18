/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:21:11 by mhida             #+#    #+#             */
/*   Updated: 2022/07/18 09:23:18 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <pthread.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# define SUCCESS 0
# define ERROR 1

typedef struct s_info
{
	size_t	sentence_cnt;
	size_t	token_cnt;
	size_t	is_in_quote;
	size_t	is_in_space;
	// size_t	token_len;
	char	*parsed_command;
}	t_info;

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *dst, const char *src, size_t n);
// void	check_builtin(char *command);
void	ft_pwd(void);
int		parse_command(char *command, t_info *info);
int		is_quote(char c, t_info *info);
int		is_space(char c, t_info *info);

#endif
