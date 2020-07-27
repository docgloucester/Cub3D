# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/05 19:04:10 by rgilles           #+#    #+#              #
#    Updated: 2020/07/05 19:04:12 by rgilles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Cub3D

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

SRCSF	= main.c parse_file.c
SRCSD	= srcs/
INCL	= includes/
LIBFT	= Libft/
MLXD	= minilibx-darwin/
MLXL	= minilibx-linux/

SRCS	=	$(addprefix $(SRCDIR),$(SRCSF))
OBJS	=	${SRCS:.c=.o}


UNAME	= $(shell uname)

%.o: %.c
#     ifeq ($(UNAME), Darwin)
		$(CC) -Wall -Wextra -Werror -I$(LIBFT) -I$(MLXD) -c $< -o $@
# 	endif
# 	ifeq ($(UNAME), Linux)
# 		$(CC) -Wall -Wextra -Werror -I$(LIBFT) -I$(MLXL) -c $< -o $@
# 	endif

$(NAME) :
	make -C $(LIBFT)
	cp $(LIBFT)libft.a ./

	ifeq ($(UNAME), Darwin)
		make -C $(MLXD)
		cp $(MLXD)libmlx.a ./
		$(CC) -framework OpenGL -framework AppKit -o $(NAME) $(OBJS) libft.a libmlx.a
	endif

	ifeq ($(UNAME), Linux)
		make -C $(MLXL)
		cp $(MLXL)libmlx.a ./
		$(CC) -lXext -lX11 -lm -lz -o $(NAME) $(OBJS) libft.a libmlx.a
	endif


