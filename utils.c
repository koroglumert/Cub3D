/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:18:48 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/09 17:18:50 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_setting *set)
{
	set->map = malloc(sizeof(t_map));
	set->mlx = malloc(sizeof(t_mlx));
	set->player = malloc(sizeof(t_player));
	set->map->north_text = NULL;
	set->map->south_text = NULL;
	set->map->west_text = NULL;
	set->map->east_text = NULL;
	set->map->map_p = NULL;
	set->map->rgb_c = malloc(sizeof(int) * 3);
	set->map->rgb_c[0] = -1;
	set->map->rgb_c[1] = -1;
	set->map->rgb_c[2] = -1;
	set->map->rgb_f = malloc(sizeof(int) * 3);
	set->map->rgb_f[0] = -1;
	set->map->rgb_f[1] = -1;
	set->map->rgb_f[2] = -1;
	set->map->img_h = 300;
	set->map->img_w = 300;
	set->map->north = malloc(sizeof(t_texture));
	set->map->south = malloc(sizeof(t_texture));
	set->map->west = malloc(sizeof(t_texture));
	set->map->east = malloc(sizeof(t_texture));
}

int	ft_free_str(t_setting *set)
{
	if (set->map->north_text)
		free (set->map->north_text);
	if (set->map->south_text)
		free (set->map->south_text);
	if (set->map->west_text)
		free (set->map->west_text);
	if (set->map->east_text)
		free (set->map->east_text);
	if (set->map->map_p)
		free (set->map->map_p);	
	if (set->map->rgb_c)
		free (set->map->rgb_c);
	if (set->map->rgb_f)
		free (set->map->rgb_f);
	return (1);
}

void	take_rgb_f_c(t_setting *set)
{
	set->map->rgb_ceiling = (set->map->rgb_c[0] << 16) 
		+ (set->map->rgb_c[1] << 8) + set->map->rgb_c[2];
	set->map->rgb_floor = (set->map->rgb_f[0] << 16) 
		+ (set->map->rgb_f[1] << 8) + set->map->rgb_f[2];
}
