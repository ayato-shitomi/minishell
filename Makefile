NAME = minishell

SRCS	=	src/minishell.c src/utils.c src/utils_2.c src/ft_pwd.c \
			src/parse_command.c src/minishell_utils.c src/execute_command.c \
			src/header.c src/ft_split_ms.c src/remove_space.c \
			src/lexical_analysis.c src/lexical_analysis_2.c \
			src/syntax_analysis.c src/ft_free.c \
			src/ft_dl_lst.c src/ft_dl_lst_2.c src/split_token_for_dquote.c \
			src/split_token_for_squote.c src/split_token_for_pipe.c \
			src/split_token_for_redirect.c src/set_token_type_dl.c \
			src/ft_sentence_lst.c src/ft_lst.c src/set_lst_of_sentence_lst.c \
			src/check_env_var_and_set_env_var_info.c src/expand_env_var.c \
			src/expand_the_expandable_in_cmd_lst.c \
			src/expand_the_expandable_in_redirect_lst.c \
			src/set_fd_by_redirect_lst.c

# src/check_builtin.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS	=	-lreadline -lhistory -L $(shell brew --prefix readline)/lib

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
