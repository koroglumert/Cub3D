# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 19:51:14 by havyilma          #+#    #+#              #
#    Updated: 2023/09/19 22:29:03 by mkoroglu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	./check_map/check_map_main.c ./check_map/check_map_textures.c ./check_map/check_valid_map.c ./check_map/check_xpm.c\
		./mlx/mlx_keys.c ./mlx/mlx_start.c ./mlx/mlx_utils.c \
		directs_and_plane.c walls_and_roses.c turning_around.c \
		utils.c utils_libft.c \
		cub3d.c 
GNL = get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
GNLOBJS = $(GNL:.c=.o)
MLX = minilibx/mlx.a
NAME = cub3d
CFLAGS = -Wall -Wextra -Werror -I./minilibx
LFLAGS = -framework AppKit -framework OpenGL -L./minilibx -lmlx
RM = rm -rf

all : $(MLX) $(NAME) $(OBJS)

$(MLX) :
	
#make -C minilibx

$(NAME) : $(OBJS) $(GNLOBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(GNLOBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) $(GNLOBJS)

fclean: clean
	@$(RM) $(NAME)

#make clean -C ./minilibx

re : fclean all

.PHONY: all clean fclean re
