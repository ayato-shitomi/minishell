NAME = minishell

SRCS	=	src/minishell.c src/utils.c src/ft_pwd.c src/parse_command.c \
			src/minishell_utils.c src/execute_command.c src/expansion.c \
			src/header.c src/ft_split_ms.c src/remove_space.c src/lexical_analysis.c \
			src/lexical_analysis_2.c src/syntax_analysis.c src/ft_free.c \
			src/ft_lst.c src/ft_lst_2.c src/split_token_for_dquote.c \
			src/split_token_for_squote.c src/split_token_for_pipe.c \
			src/split_token_for_redirect.c src/set_token_type.c \


# src/check_builtin.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS	=	-lreadline -lhistory -L $(shell brew --prefix readline)/lib

$(NAME):	$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean:		clean
	rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
