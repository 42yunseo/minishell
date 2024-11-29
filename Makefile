# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 16:46:40 by yunseo            #+#    #+#              #
#    Updated: 2024/11/26 21:06:18 by yunseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

LFLAGS = -lreadline -lft -Llibft
IFLAGS = -Ilibft/ -Iincludes/

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    LFLAGS = -lreadline -lft -Llibft -L/opt/homebrew/opt/readline/lib
    IFLAGS = -Ilibft/ -Iincludes/ -I/opt/homebrew/opt/readline/include
endif

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

BUILTIN_DIR = ./srcs/builtin/
BUILTINS = echo cd pwd export unset env exit util

ENV_DIR = ./srcs/env/
ENVS = env envp

COMMAND_DIR = ./srcs/command/
COMMANDS = command eval token expansion type ast syntax dispose parse

EXECUTE_DIR = ./srcs/execute/
EXECUTES = execute simple pipe redirect heredoc utils

SIGNAL_DIR = ./srcs/signal/
SIGNALS = signal

SRCS =	$(addsuffix .c, $(addprefix $(BUILTIN_DIR)builtin_, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix $(ENV_DIR), $(ENVS))) \
		$(addsuffix .c, $(addprefix $(COMMAND_DIR), $(COMMANDS))) \
		$(addsuffix .c, $(addprefix $(EXECUTE_DIR), $(EXECUTES))) \
		$(addsuffix .c, $(addprefix $(SIGNAL_DIR), $(SIGNALS))) \
		main.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS) $(IFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@

$(LIBFT) :
	make -sC $(LIBFT_DIR)

clean :
	rm -rf $(OBJS)
	make clean -sC $(LIBFT_DIR)

fclean :
	make clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)

re :
	make fclean
	make all

.PHONY : all clean fclean re
