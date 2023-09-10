/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_and_roses.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:58 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/10 13:12:00 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	oh_my_walls(t_setting *set)
{
	if (set->player->face_of_cube == 'x')
		set->player->distance = set->player->sidedist_x - set->player->deltadist_x;
	else
		set->player->distance = set->player->sidedist_y - set->player->deltadist_y;   //dik uzaklık olmadı bence bunlar ama neyse
	set->player->wall_height = (int)set->map->win_i / set->player->distance;
	set->player->beginning_of_the_walls = set->map->win_i / 2 - set->player->wall_height / 2;
	if (set->player->beginning_of_the_walls < 0)  // duvara çok yakın (dibinde) olma ihtimalimiz
		set->player->beginning_of_the_walls = 0;
	set->player->end_of_the_walls = set->map->win_i / 2 + set->player->wall_height / 2;
	if (set->player->end_of_the_walls >= set->map->win_i)  // duvara çok yakın (dibinde) olma ihtimalimiz
		set->player->end_of_the_walls = set->map->win_i - 1;
}

void	pixel_by_pixel (t_setting *set, int j)
{
	t_img	*wanted;
	int		texture_y;
	int		color;
	
	if (set->player->face_of_cube == 'x' && set->player->raydir_y > 0)
		wanted = set->map->north;
	else if (set->player->face_of_cube == 'x' && set->player->raydir_y < 0)
		wanted = set->map->south;
	else if (set->player->face_of_cube == 'y' && set->player->raydir_x > 0)
		wanted = set->map->west;
	else if (set->player->face_of_cube == 'y' && set->player->raydir_x < 0)
		wanted = set->map->east;
	// DEVAMI GELECEK
}
	

void	get_images(t_setting *set, int j)
{
	if (set->player->face_of_cube == 0)
		set->player->wall_x = set->player->ply_j + set->player->distance * set->player->raydir_y;
	else
		set->player->wall_x = set->player->ply_j + set->player->distance * set->player->raydir_x;
	set->player->wall_x = floor(set->player->wall_x);
	set->player->text_x = (int)(set->player->wall_x * (double)TEXT_W);
	// (diğer kodda ==>  all->rc->text_x = hit_image.img_width - all->rc->text_x - 1;)
/*	if (set->player->face_of_cube == 0 && set->player->raydir_x > 0)
		set->player->text_x = TEXT_W - set->player->text_x - 1;
	if (set->player->face_of_cube == 1 && set->player->raydir_y < 0)
		set->player->text_x = set->map->img.img_
*/
	set->player->text_step = 1.0 * TEXT_H / set->player->wall_height;
	set->player->text_pos = (set->player->beginning_of_the_walls - HEIGHT / 2 + set->player->wall_height / 2)
		* set->player->text_step;
	while (set->player->beginning_of_the_walls < set->player->end_of_the_walls)
	{
		set->player->text_pos += set->player->text_step;
		pixel_by_pixel(set, j);
		set->player->beginning_of_the_walls++;
	}
}

