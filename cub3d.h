/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:15:30 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/01 16:05:06 by havyilma         ###   ########.fr       */
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

typedef struct	s_map
{
	char	*north_text;
	char	*south_text;
	char	*west_text;
	char	*east_text;
	char	*map_p;
	char	**map;
	int		ply_x;
	int		ply_y;
	int		map_length;
	int		*rgb_c;
	int		*rgb_f;
	int		rgb_control;
}				t_map;

typedef struct s_mlx
{
	void	*mlx_init;
	void	*mlx_img;
	int		*mlx_img_addr;
	void	*mlx_window;
}				t_mlx;

void	ft_init(t_map *map);
void	ft_free_str(t_map *map);

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
char	*ft_strdup(char *s1);

int		check_texts_rgb(t_map *map, char *av1);
int		take_texts(char *str, t_map *map, int i, int flg);
int		create_map_dp(t_map *map);
int		valid_char(char *str);
int		valid_map(t_map *map);

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
