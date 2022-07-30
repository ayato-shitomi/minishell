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
# define EXPANDABLE 0
# define EXPANDABLE_QUOTED 1
# define NOT_EXPANDABLE 2
# define PIPE 3
# define REDIRECT_LEFT_ONE 4
# define REDIRECT_RIGHT_ONE 5
# define REDIRECT_LEFT_TWO 6
# define REDIRECT_RIGHT_TWO 7
# define ENVIRONMENT_VAR 8

typedef struct s_token_lst
{
	struct s_token_lst	*prev;
	struct s_token_lst	*next;
	char				*token;
	int					type;
	int					lst_first_flag;
	int					lst_last_flag;
}	t_token_lst;

typedef struct s_info
{
	size_t			token_cnt;
	size_t			is_in_dquote;
	size_t			is_in_squote;
	size_t			space_cnt;
	t_token_lst		*token_lst;
	char			*parsed_command;
	char			**split_command;
}	t_info;

/////////////////////////////////////////////////////
//   PROTOTYPES
/////////////////////////////////////////////////////

/*
void	check_builtin(char *command);
*/

// utils.c
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *dst, const char *src, size_t n);
void			*ft_calloc(size_t n, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);

// ft_pwd.c
void			ft_pwd(void);

// parse_command.c
int				parse_command(char *command, t_info *info);
char			**ft_split_ms(char const *s, t_info *info);

// minishell_utils.c
void			init_quote_flag(t_info *info);
void			quote_check(char c, t_info *info);

// set_token_type.c
void			set_token_type(char *token, t_token_lst *token_lst);

// remove_space.c
int				remove_space(char *command, t_info *info);

// lexical_analysis.c
int				lexical_analysis(t_info *info);

// lexical_analysis_2.c
void			lexical_analysis_2(t_info *info);

// split_token_for_dquote.c
int				split_token_for_dquote(t_info *info, size_t *i);

// split_token_for_squote.c
int				split_token_for_squote(t_info *info, size_t *i);

// split_token_for_pipe.c
int				split_token_for_pipe(t_info *info, size_t *i);

// split_token_for_redirect.c
int				split_token_for_redirect(t_info *info, size_t *i);

// syntax_analysis.c
int				syntax_analysis(t_info *info);

// expansion.c
int				expansion(t_info *info);

// execute_command.c
int				execute_command(t_info *info);

// header.c
void			header(void);

// ft_free.c
// void			ft_free_split_command(char **split_command);
void			ft_free_token_lst(t_info *info);

// ft_lst.c
t_token_lst		*ft_lstnew_ms(void *token);
void			ft_lstadd_back_ms(t_token_lst **lst, t_token_lst *new);
t_token_lst		*ft_lstfirst_ms(t_token_lst *lst);
t_token_lst		*ft_lstlast_ms(t_token_lst *lst);
size_t			ft_lstsize_ms(t_token_lst *lst);

// ft_lst_2.c
void			ft_lstinsert_ms(t_info *info, t_token_lst *lst, \
	size_t *i, int type);

#endif
