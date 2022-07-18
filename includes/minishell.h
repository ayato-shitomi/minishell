/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:21:11 by mhida             #+#    #+#             */
/*   Updated: 2022/07/18 10:05:01 by mhida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/////////////////////////////////////////////////////
//   INCLUDES
/////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////
//   DEFINES AND STRUCT
/////////////////////////////////////////////////////

# define SUCCESS 0
# define ERROR 1
# define PROMPT "fresh >> "
# define SHELLNAME "Fresh"

typedef struct s_info
{
	size_t	sentence_cnt;
	size_t	token_cnt;
	size_t	is_in_quote;
	size_t	is_in_space;
	// size_t	token_len;
	char	*parsed_command;
}	t_info;


/////////////////////////////////////////////////////
//   PROTOTYPES
/////////////////////////////////////////////////////

/*
void	check_builtin(char *command);
*/

// utils.c
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *dst, const char *src, size_t n);

// ft_pwd.c
void	ft_pwd(void);

// pause_command.c
int		parse_command(char *command, t_info *info);

// minishell_utils.c
int		is_quote(char c, t_info *info);
int		is_space(char c, t_info *info);

// expancion.c
int		expansion(char *command, t_info *info);

// execute_command.c
int		execute_command(char *command, t_info *info);

// header.c
void	header();

#endif
