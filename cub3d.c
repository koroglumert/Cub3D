/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:53 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/28 02:30:38 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_take_directs(t_setting *set)
{
	set->rc->dir_x = 0;
	set->rc->dir_y = 0;
	set->rc->plane_x = 0;
	set->rc->plane_y = 0;
	if (set->map->map[(int)set->rc->pos_y][(int)set->rc->pos_x] == 'E')
	{
		set->rc->dir_x = 0.99;
		set->rc->plane_y = 0.66;
	}
	if (set->map->map[(int)set->rc->pos_y][(int)set->rc->pos_x] == 'W')
	{
		set->rc->dir_x = -0.99;
		set->rc->plane_y = -0.66;
	}
	if (set->map->map[(int)set->rc->pos_y][(int)set->rc->pos_x] == 'S')
	{
		set->rc->plane_x = 0.66;
		set->rc->dir_y = 0.99;
	}
	if (set->map->map[(int)set->rc->pos_y][(int)set->rc->pos_x] == 'N')
	{
		set->rc->plane_x = -0.66;
		set->rc->dir_y = -0.99;
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

void	ft_distributor(t_setting *set)
{
	set->map->img_h = 64;
	set->map->img_w = 64;
	ft_check_xpm(set->map);
	ft_take_directs(set);
	ft_take_rgb_f_c(set);
}

int	main(int ac, char **av)
{
	t_setting	set;

	ft_init(&set);
	if (ac != 2 || check_texts_rgb(set.map, av[1]))
		return (print_error("Wrong argument count!", 0));
	if (create_map_dp(set.map)
		|| valid_char(set.map->map_p)
		|| valid_map(set.map) || where_am_i(&set, set.map->map))
		return (1);
	ft_distributor(&set);
	ft_check_double_map(set.map->map);
	mlx_start(&set);
	return (0);
}
