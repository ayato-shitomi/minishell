/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:21:11 by mhida             #+#    #+#             */
/*   Updated: 2022/07/22 13:39:10 by mhida            ###   ########.fr       */
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

typedef struct s_token_info
{
	int		type;
	char	*token;
}	t_token_info;

typedef struct s_info
{
	size_t			sentence_cnt;
	size_t			token_cnt;
	size_t			is_in_dquote; //←追加した変数 (is_in_quoteから変更)
	size_t			is_in_squote; //←追加した変数 (is_in_quoteから変更)
	size_t			space_cnt; // ←追加した変数(remove_space.cにて使用)
	// size_t			is_in_space; ←消す
	// size_t			token_len;
	t_token_info	*token_info;
	char			*parsed_command;
	char			*tmp_command;
	int				*token_type;
	char			**split_command;
}	t_info;

//↓ info.token_typeのリスト ↓

// 0 → EXPANDABLE  1 → EXPANDABLE_QUOTED  2 → NOT_EXPANDABLE  3 → PIPE  4 → REDIRECT

/////////////////////////////////////////////////////
//   PROTOTYPES
/////////////////////////////////////////////////////

/*
void	check_builtin(char *command);
*/

// utils.c
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *dst, const char *src, size_t n);
void	*ft_calloc(size_t n, size_t size);

// ft_pwd.c
void	ft_pwd(void);

// pause_command.c
int		parse_command(char *command, t_info *info);
char	**ft_split_ms(char const *s, t_info *info);

// minishell_utils.c
void	init_quote_flag(t_info *info);
void	quote_check(char c, t_info *info);

// void	quote_check(char c, t_info *info); //旧is_quote
// void	space_check_and_set_char(char *command, t_info *info, \
	//size_t i, size_t *j); //旧is_space

	//↑消す

// remove_space.c
int		remove_space(char *command, t_info *info);

// lexical_analysis.c
int		lexical_analysis(char *command, t_info *info);

// systax_analysis.c
int		syntax_analysis(char *command, t_info *info);

// expansion.c
int		expansion(char *command, t_info *info);

// execute_command.c
int		execute_command(char *command, t_info *info);

// header.c
void	header(void);

// ft_free.c
void	ft_free_split_command(char **split_command);

#endif
