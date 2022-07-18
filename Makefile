# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 09:20:42 by mhida             #+#    #+#              #
#    Updated: 2022/07/18 14:42:23 by mhida            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS	=	src/minishell.c src/utils.c src/ft_pwd.c src/parse_command.c \
			src/minishell_utils.c src/execute_command.c src/expansion.c \
			src/header.c
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
