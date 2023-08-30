/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:15:30 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/30 14:19:06 by havyilma         ###   ########.fr       */
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

void	ft_init(t_map *map);
void	ft_free_str(t_map *map);

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
char	*ft_strdup(char *s1);

int		check_texts_rgb(t_map *map, char *av1);
int		take_texts(char *str, t_map *map, int i, int flg);
int		create_map_dp(t_map *map);
int	valid_char(char *str);

#endif


/*

** altta ayrıca 2. bi map varsa diye newline kontrolü var, 
öylesine newline varsa map geçersiz sayılıyor

MAP;
herhangi bir spacein çevresinde sıfır olamaz


*/
