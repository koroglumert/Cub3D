/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_and_roses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:58 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/12 13:45:43 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	oh_my_walls(t_setting *set)
{
	if (set->player->face_of_cube == 'x')
		set->player->distance = set->player->sidedist_x - set->player->deltadist_x;
	else
		set->player->distance = set->player->sidedist_y - set->player->deltadist_y;   //dik uzaklık olmadı bence bunlar ama neyse
	set->player->wall_height = 500;
	set->player->beginning_of_the_walls = HEIGHT / 2 - 250;
	if (set->player->beginning_of_the_walls < 0)  // duvara çok yakın (dibinde) olma ihtimalimiz
		set->player->beginning_of_the_walls = 0;
	set->player->end_of_the_walls = HEIGHT / 2 + 250;
	if (set->player->end_of_the_walls >= set->map->win_i)
		set->player->end_of_the_walls = set->map->win_i - 1;
//	printf("%d   dist:%f  wall:%d  %d   %d\n", HEIGHT, set->player->distance, set->player->wall_height, set->player->beginning_of_the_walls, set->player->end_of_the_walls);
}

int	put_pixel_to_address (t_img *wesn, int x, int y, t_setting *set)
{
	(void)set;
	if (x < 0 || x > TEXT_W || y < 0 || y > TEXT_H)
		return (0);
	return (*(int *)(wesn->data + (y * wesn->sizeline) + x * wesn->bpp / 8));
}

void	pixel_by_pixel (t_setting *set, int j, int y)
{
	int		color;
/*
	if (set->player->face_of_cube == 'x' && set->player->raydir_y > 0)
		color = put_pixel_to_address(&set->map->south, set->player->text_x, set->player->text_y, set);	
	else if (set->player->face_of_cube == 'x' && set->player->raydir_y < 0)
		color = put_pixel_to_address(&set->map->north, set->player->text_x, set->player->text_y, set);	
	else if (set->player->face_of_cube == 'y' && set->player->raydir_x > 0)
		color = put_pixel_to_address(&set->map->west, set->player->text_x, set->player->text_y, set);	
	else 
		color = put_pixel_to_address(&set->map->east, set->player->text_x, set->player->text_y, set);
*/	
	color = 0x00FFFF;
//	mlx_pixel_put(set->mlx->mlx_init, set->mlx->mlx_window, j * set->mlx->bits_per_pixel / 8, set->mlx->size_line * y, color);
	set->mlx->mlx_img_addr[set->mlx->size_line * y + j * set->mlx->bits_per_pixel / 8] = color;
}
	
void	get_images(t_setting *set, int j)
{
	if (set->player->face_of_cube == 0)
		set->player->wall_x = set->player->ply_i + set->player->distance * set->player->raydir_y;
	else
		set->player->wall_x = set->player->ply_j + set->player->distance * set->player->raydir_x;
	set->player->wall_x -= floor(set->player->wall_x);
	set->player->text_x = (int)(set->player->wall_x * (double)TEXT_W);

	if (set->player->face_of_cube == 'x' && set->player->raydir_x > 0)
		set->player->text_x = TEXT_W - set->player->text_x - 1;
	if (set->player->face_of_cube == 'y' && set->player->raydir_y < 0)
		set->player->text_x = TEXT_W - set->player->text_x - 1;
	set->player->text_step = 1.0 * TEXT_H / set->player->wall_height;

	set->player->text_pos = (set->player->beginning_of_the_walls - HEIGHT / 2 + set->player->wall_height / 2)
		* set->player->text_step;
	while (set->player->beginning_of_the_walls < set->player->end_of_the_walls)
	{
		set->player->text_y = (int)(set->player->text_pos) & (TEXT_H - 1);
		set->player->text_pos += set->player->text_step;
		pixel_by_pixel(set, j, set->player->beginning_of_the_walls); 
		(void)j;
		set->player->beginning_of_the_walls++;
	}
}
