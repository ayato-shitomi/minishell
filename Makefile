NAME = minishell

SRCS	=	src/minishell.c src/utils.c src/utils_2.c src/utils_3.c src/utils_4.c \
			src/parse_command.c src/minishell_utils.c src/execute_command.c \
			src/header.c src/ft_split.c src/remove_space.c \
			src/lexical_analysis.c src/lexical_analysis_2.c \
			src/syntax_analysis.c src/check_syntax_error.c src/ft_free.c \
			src/ft_dl_lst.c src/ft_dl_lst_2.c src/split_token_for_dquote.c \
			src/split_token_for_squote.c src/split_token_for_pipe.c \
			src/split_token_for_redirect.c src/set_token_type_dl.c \
			src/ft_sentence_lst.c src/ft_lst.c src/set_lst_of_sentence_lst.c \
			src/check_env_var_and_set_env_var_info.c src/expand_env_var.c \
			src/expand_the_expandable_in_cmd_lst.c \
			src/expand_the_expandable_in_redirect_lst.c src/do_pipes.c \
			src/do_pipes_2.c src/set_fd_by_redirect_lst.c \
			src/get_next_line.c src/get_next_line_utils.c \
			src/heredoc.c src/set_pipe_fd.c src/set_fd_by_redirect_lst_2.c \
			src/heredoc_2.c src/ft_error.c src/set_sig_in_each_process.c \
			src/check_builtin.c src/builtin_cd.c src/builtin_pwd.c \
			src/builtin_exit.c src/ft_free_2.c src/builtin_cd_2.c \
			src/ft_env_var_lst.c src/ft_env_var_lst_2.c src/builtin_cd_3.c \
			src/builtin_export.c src/builtin_export_2.c src/validate.c \
			src/builtin_export_3.c src/builtin_env.c src/builtin_echo.c \
			src/builtin_unset.c src/ft_split_lex.c src/minishell_utils_2.c \
			set_sig_in_each_process2.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
# CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS	=	-lreadline -lhistory -L $(shell brew --prefix readline)/lib -I .brew/opt/readline/include

CFLAGS +=  -I$(shell brew --prefix readline)/include

LDFLAGS += -L$(shell brew --prefix readline)/lib -lreadline

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)
	@echo "set echo-control-characters off" > ~/.inputrc

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean:		clean
	rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
