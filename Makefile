# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 13:49:14 by bschwitz          #+#    #+#              #
#    Updated: 2023/01/16 18:00:36 by bschwitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MLX_PATH	= mlx/
MLX_LIB		= $(MLX_PATH)/libmlx.a

LIBFT_PATH	= libft/
LIBFT_LIB	= $(LIBFT_PATH)/libft.a

NAME	= cub3d

SRCS	= main.c \
			

OBJS	= ${SRCS:.c=.o}

CC 		= gcc

CFLAGS	= -Wall -Werror -Wextra 

RM		= rm -rf

all:	subsystems ${NAME}

%.o : %.c
		@$(CC) $(CFLAGS) -Imlx -c -o $@ $<

subsystems:
		make -C $(MLX_PATH) all
		make -C $(LIBFT_PATH) all

${NAME}:	${OBJS}
			$(CC) $(CFLAGS) \
			-Lmlx -lmlx -framework OpenGL -framework AppKit \
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

./PHONY:	all clean fclean re