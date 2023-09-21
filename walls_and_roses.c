/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_and_roses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:58 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/21 18:48:09 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_pixel_to_address (t_img *wesn, int x, int y, t_setting *set)
{
	(void)set;//MERT: bunlar neden var?
	(void)wesn;
	if (x < 0 || x > TEXT_W || y < 0 || y > TEXT_H)
		return (0);
	return (0x00FFFF);
}

void	pixel_by_pixel (t_setting *set, int x, int y)
{
	int		color;
	char	*dest;
/*
		if (set->player->face_of_cube == 'x' && set->player->raydir_y > 0)
			color = put_pixel_to_address(&set->map->south, x, y, set);	
		else if (set->player->face_of_cube == 'x' && set->player->raydir_y < 0)
			color = put_pixel_to_address(&set->map->north, x, y, set);	
		else if (set->player->face_of_cube == 'y' && set->player->raydir_x > 0)
			color = put_pixel_to_address(&set->map->west, x, y, set);	
		else 
			color = put_pixel_to_address(&set->map->east, x, y, set);
		//set->mlx->mlx_img_addr[set->mlx->size_line * set->player->pos_x + set->player->pos_y * set->mlx->bits_per_pixel / 8] = color; MERT: Deneme içiin kapattım
		y++;
		//set->player->pos_y++; //MERT: burası neden var? Seg yeme sebebiymiş 
	}
*/
	color = 0x41E093;

	dest = set->mlx->mlx_img_addr + (set->mlx->size_line * y + x * set->mlx->bits_per_pixel / 8);
	*(unsigned int *)dest = color;
	printf("x:%d\n", x);
}
	
void	ft_get_images(t_setting *set, t_player	*player, int j)
{
	if (player->face_of_cube == 'x')
		player->wall_x = player->pos_y + player->distance * player->raydir_y;
	else
		player->wall_x = player->pos_x + player->distance * player->raydir_x;
	player->wall_x -= floor(player->wall_x);
	
	player->text_x = (int)(player->wall_x * (double)TEXT_W);
	
	if (player->face_of_cube == 'x' && player->raydir_x > 0)
		player->text_x = TEXT_W - player->text_x - 1;
	if (player->face_of_cube == 'y' && player->raydir_y < 0)
		player->text_x = TEXT_W - player->text_x - 1;

	player->text_step = 1.0 * TEXT_H / player->wall_height;

	player->text_pos = (player->beginning_of_the_walls - HEIGHT / 2 + player->wall_height / 2)
		* player->text_step;
	//printf ("begin:%d  end:%d\n",player->beginning_of_the_walls,player->end_of_the_walls);
	while (player->beginning_of_the_walls <= player->end_of_the_walls)
	{
		player->text_y = (int)(player->text_pos) & (TEXT_H - 1);
		player->text_pos += player->text_step;
		pixel_by_pixel(set, j, player->beginning_of_the_walls);
		player->beginning_of_the_walls++;
	}
}
