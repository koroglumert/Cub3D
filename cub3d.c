/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:53 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/23 13:20:29 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_take_directs(t_setting *set, t_player *player)
{
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	if (set->map->map[(int)player->pos_y][(int)player->pos_x] == 'E')
	{
		player->dir_x = 1.0;
		player->plane_y = 0.66;
	}
	else if (set->map->map[(int)player->pos_y][(int)player->pos_x] == 'W')
	{
		player->dir_x = -1.0;
		player->plane_y = -0.66;
	}
	else if (set->map->map[(int)player->pos_y][(int)player->pos_x] == 'S')
	{
		player->plane_x = 0.66;
		player->dir_y = 1.0;
	}
	else if (set->map->map[(int)player->pos_y][(int)player->pos_x] == 'N')
	{
		player->plane_x = -0.66;
		player->dir_y = -1.0;
	}
	return (0);
}

static void	ft_take_rgb_f_c(t_setting *set)
{
	set->map->rgb_ceiling = (set->map->rgb_c[0] << 16)
		+ (set->map->rgb_c[1] << 8) + set->map->rgb_c[2];
	set->map->rgb_floor = (set->map->rgb_f[0] << 16)
		+ (set->map->rgb_f[1] << 8) + set->map->rgb_f[2];
}

int	main(int ac, char **av)
{
	t_setting	set;

	if (ac != 2)
	{
		printf("Error\nWrong argument count!\n");
		return (1);
	}
	ft_init(&set);
	if (check_texts_rgb(set.map, av[1]) || create_map_dp(set.map)
		|| valid_char((set.map)->map_p)
		|| valid_map(set.map) || where_am_i(&set, set.map->map))
		return (0);
	set.map->img_h = 64;
	set.map->img_w = 64;
	ft_check_xpm(set.map);
	ft_take_directs(&set, set.player);
	ft_take_rgb_f_c(&set);
	mlx_start(&set);
	return (0);
}
