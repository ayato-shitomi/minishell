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
# define CMD_LST 10
# define REDIRECT_LST 11
# define ENV_VAR_LST 12

// ここから構文解析用

typedef struct s_lst
{
	char			*str;
	char			*key; // 「lst_type == ENV_LST」の場合セット、環境変数のkey値
	char			*value; // 「lst_type == ENV_LST」の場合セット、環境変数のvalue値
	int				token_type; // ← 「EXPANDABLE 0」「ENVIRONMENT_VAR 8」etc...
	int				lst_type; // ← 「CMD_LST 10」「ENV_LST 12」etc...
	struct s_lst	*next;
}	t_lst; // 片方向線形リスト

typedef struct s_sentence_lst
{
	t_lst					*cmd_lst;
	t_lst					*redirect_lst;
	t_lst					*env_var_lst;
	struct s_sentence_lst	*next;
}	t_sentence_lst; // 片方向線形リスト (通常通り「lst」と名付け)

// ここまで構文解析用

typedef struct s_token_dl_lst
{
	struct s_token_dl_lst	*prev;
	struct s_token_dl_lst	*next;
	char					*token;
	int						type;
	int						dl_lst_first_flag;
	int						dl_lst_last_flag;
}	t_token_dl_lst; // 双方向循環リスト (双方向リストの英訳「doubly-linked list」より、「dl_lst」と定義)

typedef struct s_info
{
	size_t			is_in_dquote;
	size_t			is_in_squote;
	size_t			space_cnt;
	t_token_dl_lst	*token_dl_lst;
	char			*parsed_command;
	char			**split_command;
	t_sentence_lst	*sentence_lst;
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

// utils_2.c
char			*ft_strnstr(const char *haystack, const char *needle, \
	size_t len);
char			*ft_strjoin_three(char const *s1, char const *s2, \
	char const *s3);

// ft_pwd.c
void			ft_pwd(void);

// parse_command.c
int				parse_command(char *command, t_info *info);
char			**ft_split_ms(char const *s, t_info *info);

// minishell_utils.c
void			init_quote_flag(t_info *info);
void			quote_check(char c, t_info *info);
void			set_lst_info(t_info *info, t_lst *lst, int flag);

// set_token_type_dl.c
void			set_token_type_dl(char *token, t_token_dl_lst *token_dl_lst);

// remove_space.c
void			remove_space(char *command, t_info *info);

// lexical_analysis.c
void			lexical_analysis(t_info *info);

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

// set_lst_of_sentence_lst.c
void			set_lst_of_sentence_lst(t_info *info);

// check_env_var_and_set_env_var_info.c
void			check_env_var_and_set_env_var_info(t_info *info, t_lst *lst);

// expand_env_var.c
void			expand_env_var(t_info *info);

// expand_the_expandable_in_cmd_lst.c
int				expand_the_expandable_in_cmd_lst(t_info *info);

// expand_the_expandable_in_redirect_lst.c
int				expand_the_expandable_in_redirect_lst(t_info *info);

// execute_command.c
int				execute_command(t_info *info);

// header.c
void			header(void);

// ft_free.c
void			ft_free_token_dl_lst(t_info *info);
void			ft_free_p(char *str_env_value_p, char *str_front_p, \
	char *str_back_p);
// void			ft_free_split_command(char **split_command);

// ft_dl_lst.c
t_token_dl_lst	*ft_dl_lstnew(void *token);
void			ft_dl_lstadd_back(t_token_dl_lst **dl_lst, t_token_dl_lst *new);
t_token_dl_lst	*ft_dl_lstfirst(t_token_dl_lst *dl_lst);
t_token_dl_lst	*ft_dl_lstlast(t_token_dl_lst *dl_lst);
size_t			ft_dl_lstsize(t_token_dl_lst *dl_lst);

// ft_dl_lst_2.c
void			ft_dl_lstinsert(t_info *info, t_token_dl_lst *dl_lst, \
	size_t *i, int type);

// ft_sentence_lst.c
t_sentence_lst	*ft_sentence_lstnew(void);
void			ft_sentence_lstadd_back(t_sentence_lst **sentence_lst, \
	t_sentence_lst *new);
t_sentence_lst	*ft_sentence_lstlast(t_sentence_lst *sentence_lst);

// ft_lst.c
t_lst			*ft_lstnew(void *content);
void			ft_lstadd_back(t_lst **lst, t_lst *new);
t_lst			*ft_lstlast(t_lst *lst);

#endif
