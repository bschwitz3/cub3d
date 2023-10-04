# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 13:49:14 by bschwitz          #+#    #+#              #
#    Updated: 2023/05/08 13:40:25 by bschwitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_PATH	= mlx/
MLX_LIB		= $(MLX_PATH)/libmlx.a

LIBFT_PATH	= libft/
LIBFT_LIB	= $(LIBFT_PATH)/libft.a

NAME	= cub3D

SRCS	= main.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c \
			parsing/parse.c \
			parsing/init.c \
			parsing/init2.c \
			parsing/parse_info.c \
			parsing/parse_info2.c \
			parsing/parse_map.c \
			parsing/parse_map2.c \
			utils/utils.c \
			utils/error.c \
			utils/texture.c \
			utils/texture2.c \
			utils/mlx_utils.c \
			utils/minimap.c \
			raycasting/raycasting.c \
			raycasting/raycasting_utils.c \
			raycasting/sprites.c \
			raycasting/raycasting_moves.c \
			
			

OBJS	= ${SRCS:.c=.o}

CC 		= gcc

CFLAGS	= -Wall -Werror -Wextra

all:	subsystems ${NAME}

%.o : %.c
		@$(CC) $(CFLAGS) -Imlx -c -o $@ $<

subsystems:
		make -C $(MLX_PATH) all
		make -C $(LIBFT_PATH) all

${NAME}:	${OBJS}
			$(CC) $(CFLAGS) \
			-g -Lmlx -lmlx -framework OpenGL -framework AppKit \
			$(OBJS) \
			$(MLX_LIB) $(LIBFT_LIB) \
			-o $(NAME)

clean:
			@make -C $(MLX_PATH) clean
			@make -C $(LIBFT_PATH) clean
			$(RM) $(OBJS)

fclean:		clean
			@make -C $(MLX_PATH) clean
			@make -C $(LIBFT_PATH) fclean
			$(RM) $(NAME)

re:			fclean all

norm:		
			norminette ${SRCS} cub3d.h gnl/get_next_line.h ${LIBFT_PATH}

./PHONY:	all clean fclean re