# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yunseo <yunseo@student.42gyeongsan.kr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 16:46:40 by yunseo            #+#    #+#              #
#    Updated: 2024/11/07 18:48:16 by yunseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline -lft -Llibft
IFLAGS = -Ilibft/ -Iincludes/

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

BUILTIN_DIR = ./srcs/builtin/
BUILTINS = echo cd pwd export unset env exit

ENV_DIR = ./srcs/env/
ENVS = env envp

COMMAND_DIR = ./srcs/command/
COMMANDS = command eval token expansion type

SRCS =	$(addsuffix .c, $(addprefix $(BUILTIN_DIR)builtin_, $(BUILTINS))) \
		$(addsuffix .c, $(addprefix $(ENV_DIR), $(ENVS))) \
		$(addsuffix .c, $(addprefix $(COMMAND_DIR), $(COMMANDS))) \
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
