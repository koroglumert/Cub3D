/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_and_roses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:58 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/20 03:32:13 by mkoroglu         ###   ########.fr       */
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

void	pixel_by_pixel (t_setting *set, int y, int x)
{
	int		color;

	while (y < set->player->end_of_the_walls)
	{

		if (set->player->face_of_cube == 'x' && set->player->raydir_y > 0)
			color = put_pixel_to_address(&set->map->south, x, y, set);	
		else if (set->player->face_of_cube == 'x' && set->player->raydir_y < 0)
			color = put_pixel_to_address(&set->map->north, x, y, set);	
		else if (set->player->face_of_cube == 'y' && set->player->raydir_x > 0)
			color = put_pixel_to_address(&set->map->west, x, y, set);	
		else 
			color = put_pixel_to_address(&set->map->east, x, y, set);
		//set->mlx->mlx_img_addr[set->mlx->size_line * set->player->ply_j + set->player->ply_i * set->mlx->bits_per_pixel / 8] = color; MERT: Deneme içiin kapattım
		y++;
		//set->player->ply_i++; //MERT: burası neden var? Seg yeme sebebiymiş 
	}
	(void)color;
//	color = 0x00FFFF;
//	mlx_pixel_put(set->mlx->mlx_init, set->mlx->mlx_window, j * set->mlx->bits_per_pixel / 8, set->mlx->size_line * y, color);
}
	
void	ft_get_images(t_setting *set, t_player	*player, int j)
{
	int	y = 0;
	int x = 0;
	if (player->face_of_cube == 'x')
		player->wall_x = player->ply_i + player->distance * player->raydir_y;
	else
		player->wall_x = player->ply_j + player->distance * player->raydir_x;
	player->wall_x -= floor(player->wall_x);
	player->text_x = (int)(player->wall_x * (double)TEXT_W);
	
	if (player->face_of_cube == 'x' && player->raydir_x > 0)
		player->text_x = TEXT_W - player->text_x - 1;
	if (player->face_of_cube == 'y' && player->raydir_y < 0)
		player->text_x = TEXT_W - player->text_x - 1;
	player->text_step = 1.0 * TEXT_H / player->wall_height;

	player->text_pos = (player->beginning_of_the_walls - HEIGHT / 2 + player->wall_height / 2)
		* player->text_step;
	
	while (player->beginning_of_the_walls < player->end_of_the_walls) //MERT: burası fazladan dönüyor veya 
	{
		player->text_y = (int)(player->text_pos) & (TEXT_H - 1);
		
		player->text_pos += player->text_step;
		pixel_by_pixel(set, y++, x++);
		
		(void)j; //MERT: BU neden burda
		player->beginning_of_the_walls++;
	}
}
