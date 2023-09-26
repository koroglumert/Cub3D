/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:58 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/26 04:23:55 by havyilma         ###   ########.fr       */
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

	texture_y = (int)set->rc->text_pos & (img->img_h - 1);
	color = image_get_pixel(img, set->rc->text_x, texture_y);
	set->mlx->mlx_img_addr[set->rc->beginning_of_the_walls
		* WIDTH + x] = color;
}

t_img	get_side_image(t_setting *set)
{
	if (set->rc->face_of_cube == 'x' && set->rc->raydir_x > 0)
		return (set->map->south);
	else if (set->rc->face_of_cube == 'x' && set->rc->raydir_x < 0)
		return (set->map->north);
	else if (set->rc->face_of_cube == 'y' && set->rc->raydir_y > 0)
		return (set->map->west);
	else
		return (set->map->east);
}

void	ft_get_images(t_setting *set, t_rc	*rc, int x)
{
	t_img	hit;

	hit = get_side_image(set);
	if (rc->face_of_cube == 'x')
		rc->wall_x = rc->pos_y + rc->distance * rc->raydir_y;
	else
		rc->wall_x = rc->pos_x + rc->distance * rc->raydir_x;
	rc->wall_x -= floor((rc->wall_x));
	rc->text_x = (int)(rc->wall_x * (double)hit.img_w);
	if (rc->face_of_cube == 0 && rc->raydir_x > 0)
		rc->text_x = hit.img_w - rc->text_x - 1;
	if (rc->face_of_cube == 1 && rc->raydir_y < 0)
		rc->text_x = hit.img_w - rc->text_x - 1;
	rc->text_step = 1.0 * hit.img_w / rc->wall_height;
	rc->text_pos = (rc->beginning_of_the_walls - HEIGHT / 2
			+ rc->wall_height / 2) * rc->text_step;
	while (rc->beginning_of_the_walls <= rc->end_of_the_walls)
	{
		rc->text_pos += rc->text_step;
		image_put_pixel(&hit, x, set);
		rc->beginning_of_the_walls++;
	}
}
