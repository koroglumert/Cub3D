/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:46:23 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/20 22:43:08 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	paint_cloud_and_grass(t_setting *set)
{
	int	x;
	int	y;
	char *test;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			//printf("	XXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
			if (y < HEIGHT / 2) 
			{
				
				test =  set->mlx->mlx_img_addr + (y * set->mlx->size_line + (x * set->mlx->bits_per_pixel / 8));
				*(unsigned int *)test = set->map->rgb_ceiling; 
			}
			
			else
			{
				test =  set->mlx->mlx_img_addr + (y * set->mlx->size_line + (x * set->mlx->bits_per_pixel / 8));
				*(unsigned int *)test = set->map->rgb_floor;
			}
			y++;
		}
		x++;
	}
}

