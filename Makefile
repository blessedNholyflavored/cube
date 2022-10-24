NAME =		cub3D

SRCS =		srcs/check_arg.c srcs/check_arg2.c srcs/check_map.c \
			srcs/check.c srcs/ft_atoi.c srcs/get_next_line.c srcs/main.c \
			srcs/set_map.c srcs/utils.c srcs/utils2.c srcs/init_window.c \
			srcs/raycasting.c srcs/move_player.c srcs/move_camera.c srcs/render.c \
			srcs/init_functions.c srcs/check_map2.c srcs/key_press.c srcs/check_arg3.c \
			srcs/error.c

_DEPS =		cub.h

INCL =		./include/

DEPS =		$(patsubst %,$(INCL)/%,$(_DEPS))

OBJS =		${SRCS:.c=.o}

CC =		clang

RM =		rm -f

CFLAGS =	-Wall -Werror -Wextra -g3

MLX =		./minilibx

MLX_LIB = 	./minilibx/libmlx_Linux.a

.c.o:		${DEPS}
		${CC} ${CFLAGS} -I${INCL} -I${MLX} -g3 -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} $(MLX_LIB)
		${CC} ${CFLAGS}  ${OBJS} -o ${NAME} ${MLX_LIB}\
		-L -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

$(MLX_LIB):
		make -C ${MLX} -j


all:		${NAME}

clean:		
		${RM} ${OBJS}
		make clean -C ${MLX}

fclean:		clean
		${RM} ${NAME}
		${RM} ${NAME} ${MLX_LIB}

re:		fclean
		$(MAKE) all -j

.PHONY:		all clean fclean re

#-framework OpenGL -framework AppKit
