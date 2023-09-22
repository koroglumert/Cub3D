/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:46:23 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/22 21:35:23 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	paint_cloud_and_grass(t_setting *set)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				set->mlx->mlx_img_addr[y * WIDTH  + x] = (int)set->map->rgb_ceiling;
			else
				set->mlx->mlx_img_addr[y * WIDTH + x] = (int)set->map->rgb_floor;
			y++;
		}
		x++;
	}
}

