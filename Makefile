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

LNFLM	= -framework OpenGL -framework AppKit
LNFLL	= -lXext -lX11 -lm -lz

SRCSF	= main.c parse_file.c
SRCSD	= srcs/
INCL	= includes/
LIBFT	= Libft/

MLXD	= minilibx-darwin/
MLXL	= minilibx-linux/

SRCS	=	$(addprefix ${SRCDIR},${SRCSF})
OBJS	=	${SRCS:.c=.o}


UNAME	= ${shell uname -s}

ifeq (${UNAME}, Darwin)
	MLX 	= ${MLXD}
	LINKFL 	= ${LNFLM}
else
	MLX		= ${MLXL}
	LINKFL	= ${LNFLL}
endif

.c.o:
			${CC} ${CFLAGS} -I${LIBFT} -I${MLX} -c $< -o ${<:.c=.o}


${NAME} :	${OBJS}
			make -C ${LIBFT}
			cp ${LIBFT}libft.a ./
			make -C ${MLX}
			cp ${MLX}libmlx.a ./
			${CC} ${LINKFL} -o ${NAME} ${OBJS} libft.a libmlx.a


all :		${NAME}

clean :
			find . -type f -name "*.o" -delete

fclean :	clean
			find . -type f -name "*.a" -delete
			rm -rf ${NAME}

re :		fclean all

.PHONY :	re clean fclean