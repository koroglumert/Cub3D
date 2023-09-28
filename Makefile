SRCS =	./check_map/check_map_main.c ./check_map/check_map_textures.c ./check_map/check_valid_map.c ./check_map/check_xpm.c ./check_map/check_map_utils.c \
		./mlx/mlx_keys.c ./mlx/mlx_start.c\
		./ray_casting/ray_casting.c ./ray_casting/get_images.c ./ray_casting/turning_around.c \
		utils.c cub3d.c mert.c
GNL = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
GNLOBJS = $(GNL:.c=.o)
MLX = minilibx/mlx.a
NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./minilibx
LFLAGS = -framework AppKit -framework OpenGL -L./minilibx -lmlx 
RM = rm -rf

all : $(MLX) $(NAME) $(OBJS)

$(MLX) :
#	make -C minilibx

$(NAME) : $(OBJS) $(GNLOBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(GNLOBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) $(GNLOBJS)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) ./get_next_line/*.o
#	@$(RM) ./minilibx/*.o

re : fclean all

.PHONY: all clean fclean re
