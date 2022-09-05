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
# include <stdbool.h>

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
# define BUFFER_SIZE 1
# define CMD_NOT_FOUND "command not found"
# define E_STATUS_CNF 127
# define E_STATUS_SYN_ERR 258
# define PERM_DENIED "Permission denied"
# define NO_FILE "No such file or directory"
# define NOT_VI "not a valid identifier"

typedef struct s_env_var_lst
{
	struct s_env_var_lst	*prev;
	struct s_env_var_lst	*next;
	char					*key;
	char					*value;
}	t_env_var_lst; // 双方向線形リスト 環境変数用

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
	int						is_cat_with_next;
}	t_token_dl_lst; // 双方向循環リスト (双方向リストの英訳「doubly-linked list」より、「dl_lst」と定義)

typedef struct s_info
{
	size_t				is_in_dquote;
	size_t				is_in_squote;
	size_t				space_cnt;
	t_token_dl_lst		*token_dl_lst;
	char				*parsed_command;
	char				**split_command;
	t_sentence_lst		*sentence_lst;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	t_env_var_lst		*env_var_lst;
	int					fd_for_restore;
	int					fd_in_restore_flag;
	int					fd_out_restore_flag;
	int					red_left_after_right_flag;
	int					exit_status;
}	t_info;

/////////////////////////////////////////////////////
//   PROTOTYPES
/////////////////////////////////////////////////////

// check_builtin.c
int				check_builtin(char **cmd);
int				exec_builtin(t_info *info, char **cmd);
int				exec_builtin_without_pipe(t_info *info);

// builtin_cd.c
int				ft_cd(t_info *info);

// builtin_cd_2.c
char			*get_env_value(t_info *info, char *key);
void			set_env_value(t_info *info, char *env_key, \
	char *env_value_for_set);
int				ft_cd_case_absolute_path(t_info *info, char *dest_dir);
int				ft_cd_case_multiple_relative_paths(t_info *info, \
	char *dest_dir, size_t delimiter_cnt_for_tilde);

// builtin_cd_3.c
void			ft_cd_case_branch(t_info *info, char *dest_dir, \
	size_t delimiter_cnt_for_tilde);
void			ft_cd_case_tilde(t_info *info);
void			ft_cd_case_dot1(t_info *info);
void			ft_cd_case_dot2(t_info *info);
void			ft_cd_case_each_relative_path(t_info *info, char *dest_dir);

// builtin_pwd.c
int				ft_pwd(t_info *info);

// builtin_unset.c

int				ft_unset(t_info *info);

// builtin_export.c
int				ft_export(t_info *info);

// builtin_export_2.c
int				ft_export_case_have_arg(t_info *info);
void			ft_set_env(t_info *info, char *value);
void			ft_print_env(char *key, char *value, int is_export);

// builtin_echo.c
//int				ft_echo(char *str, bool flag_n);
int					ft_echo(t_info *info);

// builtin_exit.c
int				ft_exit(size_t ac, char **cmd, t_lst *cmd_lst);
// void			ft_exit(int argc, char *argv[]);

// builtin_env.c
int				ft_env(t_info *info);

// utils.c
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *dst, const char *src, size_t n);
void			*ft_calloc(size_t n, size_t size);
char			*ft_strdup(const char *src);

// utils_2.c
char			*ft_strnstr(const char *haystack, const char *needle, \
	size_t len);
char			*ft_strjoin_three(char const *s1, char const *s2, \
	char const *s3);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strcpy(char *dst, char *src);

// utils_3.c
char			*ft_strchr(const char *str, int chr);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
int				ft_atoi(const char *str);

// utils_4.c
int				ft_isalnum(int n);
char			*ft_itoa(int n);

// ft_error.c
void			error_and_exit(char *error_str_1, char *error_str_2, \
	int exit_status);
int				error_and_return(char *cmd, char *arg, char *err_msg);

// parse_command.c
int				parse_command(char *command, t_info *info);

// ft_split.c
char			**ft_split(char const *s, char c);

// ft_split_lex.c
char			**ft_split_lex(char const *s, char c);

// minishell_utils.c
void			init_quote_flag(t_info *info);
void			quote_check(char c, t_info *info);
void			set_lst_info(t_info *info, t_lst *lst, int flag);
int				pipe_and_error_check(int pipe_fd[2]);
int				fork_and_error_check(pid_t *pid);

// minishell_utils_2.c
int				set_exit_status(t_info *info, int exit_status);

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
void			syntax_analysis(t_info *info);

// set_lst_of_sentence_lst.c
void			set_lst_of_sentence_lst(t_info *info);

// check_env_var_and_set_env_var_info.c
void			check_env_var_and_set_env_var_info(t_info *info, t_lst *lst);

// check_syntax_error.c
int				check_syntax_error(t_info *info);

// expand_env_var.c
void			expand_env_var(t_info *info);

// expand_the_expandable_in_cmd_lst.c
int				expand_the_expandable_in_cmd_lst(t_info *info);

// expand_the_expandable_in_redirect_lst.c
int				expand_the_expandable_in_redirect_lst(t_info *info);

// execute_command.c
int				execute_command(t_info *info);

// do_pipes.c
int				do_pipes(t_info *info, size_t i, \
	size_t cmd_cnt);
int				set_cmd_fd_and_exec(t_info *info, pid_t pid);

// do_pipes_2.c
void			set_sentence_lst_and_pipe_fd(t_info *info, \
	size_t cmd_cnt, int pipe_fd[2], size_t i);
int				set_pipe_and_fork(int pipe_fd[2], pid_t *pid);
int				check_first_sentence(t_info *info, size_t i, \
	size_t cmd_cnt);
char			**get_envp_in_array(t_info *info);

// set_sig_in_each_process.c
void			init_sig(t_info *info);
void			set_sig_in_child_process(t_info *info);
void			set_sig_in_parent_process(t_info *info);

// set_fd_by_redirect_lst.c
int				set_fd_by_redirect_lst(t_info *info);

// set_fd_by_redirect_lst_2.c
void			init_and_set_fd_for_restore(t_info *info, int n);
int				set_fd_case_red_left_one(t_info *info);
int				set_fd_case_red_right_one(t_info *info);
int				set_fd_case_red_right_two(t_info *info);

// heredoc.c
int				heredoc(t_info *info);
void			set_continue_flag(t_sentence_lst *sentence_lst, \
	int *continue_flag);

// heredoc_2.c
int				heredoc_parent_process(t_info *info, \
	int heredoc_pipe_fd[2], int continue_flag);

// set_pipe_fd.c
void			set_pipe_fd_0(int pipe_fd[2]);
void			set_pipe_fd_1(int pipe_fd[2]);
void			set_pipe_fd_2(t_sentence_lst *sentence_lst, int pipe_fd[2]);

// header.c
void			header(void);

// ft_free.c
void			ft_free_token_dl_lst(t_info *info);
void			ft_free_p(char *str_env_value_p, char *str_front_p, \
	char *str_back_p, char *str_p);
void			ft_free_sentence_lst(t_info *info);
void			ft_free_cmd(char **cmd);

// ft_free_2.c
void			free_env_var_lst(t_info *info);

// validate.c
int				validate_arg_at_ft_export(t_info *info);

// ft_dl_lst.c
t_token_dl_lst	*ft_dl_lstnew(void *token);
void			ft_dl_lstadd_back(t_token_dl_lst **dl_lst, t_token_dl_lst *new);
t_token_dl_lst	*ft_dl_lstfirst(t_token_dl_lst *dl_lst);
t_token_dl_lst	*ft_dl_lstlast(t_token_dl_lst *dl_lst);
size_t			ft_dl_lstsize(t_token_dl_lst *dl_lst);

// ft_dl_lst_2.c
void			ft_dl_lstinsert(t_info *info, t_token_dl_lst *dl_lst, \
	size_t *i, int type);
void			ft_dl_lstcat(t_info *info);

// ft_sentence_lst.c
t_sentence_lst	*ft_sentence_lstnew(void);
void			ft_sentence_lstadd_back(t_sentence_lst **sentence_lst, \
	t_sentence_lst *new);
t_sentence_lst	*ft_sentence_lstlast(t_sentence_lst *sentence_lst);
size_t			ft_sentence_lstsize(t_sentence_lst *sentence_lst);

// ft_lst.c
t_lst			*ft_lstnew(void *content);
void			ft_lstadd_back(t_lst **lst, t_lst *new);
t_lst			*ft_lstlast(t_lst *lst);
size_t			ft_lstsize(t_lst *lst);

// ft_env_var_lst.c
void			init_env_var_lst(t_info *info);
t_env_var_lst	*ft_env_var_lstnew(char *key, char *value);
void			ft_env_var_lstadd_back(t_env_var_lst **env_var_lst, \
	t_env_var_lst *new);
t_env_var_lst	*ft_env_var_lstlast(t_env_var_lst *env_var_lst);

// ft_env_var_lst_2.c
size_t			ft_env_var_lstsize(t_env_var_lst *env_var_lst);
void			ft_env_var_lstinsert(t_info *info, t_env_var_lst *new, \
	t_env_var_lst *env_var_lst_tmp, size_t i);

// get_next_line.c
int				get_next_line(int fd, char **line);

// get_next_line_utils.c
size_t			ft_strchr_i(const char *str, int chr, int *flag);
char			*ft_bufcat(char *tmp, char *buf, size_t buf_i);

#endif
