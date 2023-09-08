/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:15:30 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/08 05:46:56 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CUB3D_H

#define CUB3D_H

#include <math.h>
#include "get_next_line/get_next_line.h"
#include "minilibx/mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct	s_img
{
	void	*window;
	int		*image;
	char	*data;
	int		bpp; 
	int		sizeline;
	int		endian; 	
}				t_img;

typedef struct s_texture{
	void	*image;
	char	*path;
	char	*data;
	int		use;
	int		w;
	int		h;
	int		bpp;
	int		sizeline;
	int		endian;
}			t_texture;

typedef struct	s_player{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	speed;
	double	rot_speed;
	double	plane_x;
	double	plane_y;
}				t_player;

typedef struct	s_map
{
	char		*north_text;
	char		*south_text;
	char		*west_text;
	char		*east_text;
	char		*map_p;
	char		**map;
	int			ply_x;
	int			ply_y;
	int			map_length;
	int			*rgb_c;
	int			*rgb_f;
	int			rgb_ceiling;
	int			rgb_floor;
	int			rgb_control;
	t_texture	*north;
	t_texture	*south;
	t_texture	*west;
	t_texture	*east;
	int			img_h;
	int			img_w;
	t_img		img;
	int			win_j;
	int			win_i;
}				t_map;

typedef struct s_mlx
{
	void	*mlx_init;
	void	*mlx_img;
	char	*mlx_img_addr;
	void	*mlx_window;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_mlx;

typedef struct	s_setting
{
	t_map		*map;
	t_mlx		*mlx;
	t_player	*player;
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
int		ft_free_str(t_setting *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
char	*ft_strdup(char *s1);

int		check_texts_rgb(t_map *map, char *av1);
int		take_texts(char *str, t_map *map, int i, int flg);
int		create_map_dp(t_map *map);
int		valid_char(char *str);
int		valid_map(t_map *map);
void	start_mlx(t_setting *set);

#endif


/*

** altta ayrıca 2. bi map varsa diye newline kontrolü var, 
öylesine newline varsa map geçersiz sayılıyor
-------------------
 As such, I came up with a few map validation rules. Assume that we are scanning the map from top to bottom, left to right :

 Ignore all leading whitespaces.
 If the current row is the 0th row or the final row, only accept '1’s and ’ 's.
 else, The first and final character should always be a ‘1’.
 In the case of any non leading whitespaces, the only acceptable characters adjacent to the space are '1’s or ’ 's.
 If strlen(curr_row) > strlen(row_on_top) && current col > strlen(row_on_top), current character should be ‘1’
 If strlen(curr_row) > strlen(row_on_bottom) && current col > strlen(row_on_bottom), current character should be ‘1’
-------------------
https://hackmd.io/@nszl/H1LXByIE2
*/
