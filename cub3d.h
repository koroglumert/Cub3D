/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:15:30 by havyilma          #+#    #+#             */
/*   Updated: 2023/10/07 20:02:12 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include <math.h>
# include "get_next_line/get_next_line.h"
# include "minilibx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_img
{
	void	*window;
	void	*image;
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;
	int		img_h;
	int		img_w;
}				t_img;

typedef struct s_rc{
	double		dir_x;
	double		dir_y;
	double		speed;
	double		plane_x;
	double		plane_y;
	double		pos_x;
	double		pos_y;
	int			map_y;
	int			map_x;
	double		camera_x;
	double		camera_y;
	double		raydir_x;
	double		raydir_y;
	double		deltadist_x;
	double		deltadist_y;
	double		sidedist_x;
	double		sidedist_y;
	int			move_x;
	int			move_y;
	int			face_of_cube;
	double		distance;
	int			wall_height;
	int			beginning_of_the_walls;
	int			end_of_the_walls;
	double		wall_x;
	double		wall_y;
	int			text_x;
	int			text_y;
	double		text_pos;
	double		text_step;
	char		start_position;
}				t_rc;

typedef struct s_map{
	char			*north_text;
	char			*south_text;
	char			*west_text;
	char			*east_text;
	char			*map_p;
	char			**map;
	int				map_length;
	int				*rgb_c;
	int				*rgb_f;
	int				rgb_ceiling;
	int				rgb_floor;
	int				rgb_control;
	t_img			north;
	t_img			south;
	t_img			west;
	t_img			east;
	int				img_h;
	int				img_w;
}					t_map;

typedef struct s_mlx{
	void	*mlx_init;
	void	*mlx_img;
	int		*mlx_img_addr;
	void	*mlx_window;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_mlx;

typedef struct s_setting{
	t_map		*map;
	t_mlx		*mlx;
	t_rc		*rc;
	double		move_speed;
	double		rot_speed;
	int			press_w;
	int			press_a;
	int			press_s;
	int			press_d;
	int			direct_right;
	int			direct_left;
}				t_setting;

void	ft_init(t_setting *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
char	*ft_strdup(char *s1);
int		check_texts_rgb(t_map *map, char *av1);
void	ft_check_xpm(t_map *map);
int		take_texts(char *str, t_map *map, int i, int flg);
int		create_map_dp(t_map *map);
int		valid_char(char *str);
int		valid_map(t_map *map);
int		where_am_i(t_setting *set, char **str);
void	mlx_start(t_setting *set);
int		my_screen(t_setting *set);
int		close_win(t_setting *set);
int		press_key(int keycode, t_setting *set);
int		release_key(int keycode, t_setting *set);
void	ray_casting(t_setting *set);
void	ft_get_images(t_setting *set, t_rc	*rc, int j);
void	check_keys(t_setting *set);
void	ft_images_management(t_mlx *mlx, t_map *map);
void	ft_init_mlx(t_mlx *mlx);
int		print_error(char *str, int t);
int		check_if_them_full(t_map *map);
int		while_for_space(char *str, int *i);
void	fill_sing_pnt(char *add, t_map *map);
void	ft_dp_2(t_map *map, int length);
void	ft_check_double_map(char **str);
char	**ft_copy_double_array(char **str);
void	ft_free_double_array(char **str);
int		return_value(char *str, int i, int rgb);

# define TEXT_W 64
# define TEXT_H 64
# define WIDTH 1920
# define HEIGHT 1080

# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define RIGHT 124
# define LEFT 123

#endif
