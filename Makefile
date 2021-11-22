# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcanon <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 00:56:42 by hcanon            #+#    #+#              #
#    Updated: 2019/11/19 18:23:25 by hcanon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_GEN		=	${SRCS_GEN:.c=.o}
OBJS_DIS		=	${SRCS_DIS:.c=.o}
OBJS_ALGO		=	${SRCS_ALGO:.c=.o}
OBJS_PARS		=	${SRCS_PARS:.c=.o}
OBJS_GNL		=	${SRCS_GNL:.c=.o}
SRCS_PARS		=	srcs/map_parsing/map_parsing.c		\
					srcs/map_parsing/texture_parsing.c	\
					srcs/map_parsing/error_managmnt.c	\
					srcs/map_parsing/line_parsing.c
SRCS_GNL		=	srcs/gnl/get_next_line.c			\
					srcs/gnl/get_next_line_utils.c
SRCS_GEN		=	srcs/general/starter.c				\
					srcs/general/save.c					\
					srcs/general/event.c				\
					srcs/general/end.c
SRCS_ALGO		=	srcs/algo/inter.c					\
					srcs/algo/algo.c
SRCS_DIS		=	srcs/display/display.c
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g -I ${HEADER}
CFLAGS_MLX		=	-lmlx -L ./minilibX/ -lXext -lX11
CFLAGS_TEST		=	-g3 -fsanitize=address
NAME			=	Cub3D
HEADER			=	./includes/

$(NAME):	make_libs test

make_libs:
			$(MAKE) all -C ./libft/
			$(MAKE) all -C ./minilibX/

all:		$(NAME)

test:		${OBJS_PARS} ${OBJS_GNL} ${OBJS_GEN} ${OBJS_ALGO} ${OBJS_DIS}
			${CC} ${CFlAGS_TEST} ${CFLAGS} -o ${NAME} ${OBJS_PARS} ${OBJS_GNL} ${OBJS_GEN} ${OBJS_ALGO} ${OBJS_DIS} ./libft/libft.a ${CFLAGS_MLX} ./minilibX/libmlx.a -lm

clean:
			$(MAKE) clean -C ./libft/
			rm -f ${OBJS_PARS} ${OBJS_GEN} ${OBJS_GNL} ${OBJS_ALGO} ${OBJS_DIS}

fclean:		clean
			$(MAKE) fclean -C ./libft/
			rm -f ${NAME}

re:			fclean ${NAME}

.PHONY:		all clean fclean re test make_libs
