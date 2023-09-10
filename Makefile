# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 19:51:14 by havyilma          #+#    #+#              #
#    Updated: 2023/09/10 11:16:20 by havyilma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -I./minilibx
LFLAGS = -framework AppKit -framework OpenGL -L./minilibx -lmlx
MLX = minilibx/mlx.a
GNL = get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
GNLOBJS = $(GNL:.c=.o)
SRCS = libft.c main.c check_map_main.c utils.c check_map_textures.c check_valid_map.c xpm.c mlx_utils.c\
		press_keys.c ray_casting.c directs_and_plane.c walls_and_roses.c
OBJS = $(SRCS:.c=.o)
NAME = cub3d

all : $(MLX) $(NAME) $(OBJS)

$(MLX) :
	make -C minilibx

$(NAME) : $(OBJS) $(GNLOBJS)
	gcc $(CFLAGS) $(OBJS) $(GNLOBJS) $(LFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS) $(NAME)

fclean:
	rm -rf $(OBJS) $(NAME)
	rm -rf ../get_next_line/*.o
	make clean -C ./minilibx

re : fclean all

.PHONY: all clean fclean re
