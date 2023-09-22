/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 11:01:58 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/22 21:59:50 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	set->mlx->mlx_img_addr[set->player->beginning_of_the_walls * WIDTH + x] = color;
}

t_img	get_side_image(t_setting *set)
{
	if (set->player->face_of_cube == 'x' && set->player->raydir_x > 0)
		return (set->map->south); // bence N
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


/*
	player->wall_x -= floor(player->wall_x);
	
	
	player->text_x = (int)(player->wall_x * (double)TEXT_W);
	if (player->face_of_cube == 'x' && player->raydir_x > 0)
		player->text_x = TEXT_W - player->text_x - 1;
	if (player->face_of_cube == 'y' && player->raydir_y < 0)
		player->text_x = TEXT_W - player->text_x - 1;
	player->text_step = 1.0 * TEXT_H / player->wall_height;
	player->text_pos = (player->beginning_of_the_walls - HEIGHT / 2 + player->wall_height / 2)
		* player->text_step;
	

	while (player->beginning_of_the_walls <= player->end_of_the_walls)
	{
		player->text_y = (int)(player->text_pos) & (TEXT_H - 1);
		player->text_pos += player->text_step;
		pixel_by_pixel(set, j, player->beginning_of_the_walls);
		player->beginning_of_the_walls++;
	}
*/
/*
	double flordeger = player->wall_x - floor(player->wall_x);
	ratio_x = (int)(flordeger * TEXT_W);
	if (player->beginning_of_the_walls > player->end_of_the_walls)
	{
		int tmp = player->beginning_of_the_walls;
		player->beginning_of_the_walls = player->end_of_the_walls ;
		player->end_of_the_walls = tmp;
	}	
	int pikselYuksek =player->end_of_the_walls -  player->beginning_of_the_walls;
	if (pikselYuksek < 0)
		pikselYuksek *= -1;
	else if (pikselYuksek == 0)
		return ;
	//printf("and begin %d ve end = %d\n", player->beginning_of_the_walls, player->end_of_the_walls);
	while (player->beginning_of_the_walls <= player->end_of_the_walls)
	{
		images_addr = (set->mlx->mlx_img_addr + (player->beginning_of_the_walls * set->mlx->size_line + (j * set->mlx->bits_per_pixel / 8)));
		*(int *)images_addr = 0xFFFFFF;
		ratio_y = TEXT_H / pikselYuksek ;
		if (player->face_of_cube == 'x' && player->raydir_x > 0) //eeast
			*images_addr = *(set->map->east.data + (ratio_y * set->map->east.sizeline + (ratio_x * set->mlx->bits_per_pixel / 8)));
		else if (player->face_of_cube == 'x' && player->raydir_x < 0) //west
			*images_addr = *(set->map->east.data + (ratio_y * set->map->west.sizeline + (ratio_x * set->mlx->bits_per_pixel / 8)));
		else if (player->face_of_cube == 'y' && player->raydir_y < 0) // north
			*images_addr = *(set->map->east.data + (ratio_y * set->map->north.sizeline + (ratio_x * set->mlx->bits_per_pixel / 8)));
		else if (player->face_of_cube == 'y' && player->raydir_y > 0) //south
			*images_addr = *(set->map->east.data + (ratio_y * set->map->south.sizeline + (ratio_x * set->mlx->bits_per_pixel / 8)));
		if (player->beginning_of_the_walls == 288 && player->end_of_the_walls == 352)
			printf("veri %c \n", *images_addr);
		player->beginning_of_the_walls++;
	}
*/


/*
void	pixel_by_pixel (t_setting *set, char *img_data, int ratio_x, int ratio_y, int x, int y)
{
	char	*dest;
	int x = 0;

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

	dest = set->mlx->mlx_img_addr + (set->mlx->size_line * y + (x * set->mlx->bits_per_pixel / 8));
	dest = img_data + 
}
	*/
