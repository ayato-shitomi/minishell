# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhida <mhida@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 09:20:42 by mhida             #+#    #+#              #
#    Updated: 2022/07/18 09:58:56 by mhida            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = minishell.c utils.c ft_pwd.c parse_command.c \
		minishell_utils.c execute_command.c expansion.c \
		# check_builtin.c


OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory -L $(shell brew --prefix readline)/lib

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
