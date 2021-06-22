# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yihssan <yihssan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/09 14:48:08 by laafilal          #+#    #+#              #
#    Updated: 2021/06/16 16:16:22 by yihssan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	minishell

CC = gcc

FLAGS = -Wall -Werror -Wextra -g 
#-fsanitize=address -g

IDIR = -I. -I./libft -I../libft -I.. -I.

LIB = -L./libft -lft -lncurses

MSRC = minishell.c

SUBSRCS = ft_d_list.c init_shell.c line_handler.c minishell_utils.c newparser.c \
			exec.c notbuilt.c notbuilt2.c notbuilt3.c notbuilt4.c init_env.c utils.c signals_handler.c init_exec.c utils_exec.c exec_tools.c process.c \
			env_utils.c set_shlvl.c list_free.c file_manager.c check_builtins.c built_ins.c ft_atol.c ft_split2.c\
			parsing_tools.c parsing_tools2.c parsing_tools3.c parsing_tools4.c parsing_tools5.c parsing_tools6.c parsing_tools7.c parsing_tools8.c parsing_tools9.c parsing_tools10.c parsing_tools11.c

SUBOBJS = $(SUBSRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(addprefix ./srcs/,$(SUBOBJS)) | ./libft/libft.a
	$(CC) $(FLAGS) $(IDIR) $(MSRC) -o $(NAME) $(addprefix ./srcs/,$(SUBOBJS)) $(LIB)

$(addprefix ./srcs/,$(SUBOBJS)):
	cd srcs && $(CC) $(FLAGS) $(IDIR) -c $(SUBSRCS)

./libft/libft.a: ./libft/libft.h
	cd libft && $(MAKE) bonus && $(MAKE)

bonus:

clean:
		/bin/rm -f *.o
		/bin/rm -f ./srcs/*.o
		cd libft && $(MAKE) clean

fclean: clean
		/bin/rm -f $(NAME)
		cd libft && $(MAKE) fclean

re: fclean all ./libft/libft.a
