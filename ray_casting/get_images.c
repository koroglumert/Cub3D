/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:58 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/23 13:21:18 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	image_get_pixel(t_img *img, int x, int y)
{
	if (x < 0 || x > img->img_w || y < 0 || y > img->img_h)
		return (0);
	return (*((int *)(img->data + (y * img->sizeline) + (x * 4))));
}

void	image_put_pixel(t_img *img, int x, t_setting *set)
{
	int	texture_y;
	int	color;

	texture_y = (int)set->player->text_pos & (img->img_h - 1);
	color = image_get_pixel(img, set->player->text_x, texture_y);
	set->mlx->mlx_img_addr[set->player->beginning_of_the_walls
		* WIDTH + x] = color;
}

t_img	get_side_image(t_setting *set)
{
	if (set->player->face_of_cube == 'x' && set->player->raydir_x > 0)
		return (set->map->south);
	else if (set->player->face_of_cube == 'x' && set->player->raydir_x < 0)
		return (set->map->north);
	else if (set->player->face_of_cube == 'y' && set->player->raydir_y > 0)
		return (set->map->west);
	else
		return (set->map->east);
}

void	ft_get_images(t_setting *set, t_player	*player, int x)
{
	t_img	hit;

	hit = get_side_image(set);
	if (player->face_of_cube == 'x')
		player->wall_x = player->pos_y + player->distance * player->raydir_y;
	else
		player->wall_x = player->pos_x + player->distance * player->raydir_x;
	player->wall_x -= floor((player->wall_x));
	player->text_x = (int)(player->wall_x * (double)hit.img_w);
	if (player->face_of_cube == 0 && player->raydir_x > 0)
		player->text_x = hit.img_w - player->text_x - 1;
	if (player->face_of_cube == 1 && player->raydir_y < 0)
		player->text_x = hit.img_w - player->text_x - 1;
	player->text_step = 1.0 * hit.img_w / player->wall_height;
	player->text_pos = (player->beginning_of_the_walls - HEIGHT / 2
			+ player->wall_height / 2) * player->text_step;
	while (player->beginning_of_the_walls <= player->end_of_the_walls)
	{
		player->text_pos += player->text_step;
		image_put_pixel(&hit, x, set);
		player->beginning_of_the_walls++;
	}
}
