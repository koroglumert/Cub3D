/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:46:23 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/12 03:54:44 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	where_am_i(t_setting *set, char **str)
{
	int	i;
	int j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 'N' || str[i][j] == 'S' || str[i][j] == 'W' || str[i][j] == 'E')
			{
				set->player->ply_i = i;
				set->player->ply_j = j;
				return (0);
			}
		}
	}
	return(0);
}

void	player_coordinate (t_setting *set)
{
	set->player->x = (double)(set->player->ply_j) + 0.5;
	set->player->y = (double)(set->player->ply_i) + 0.5;
}

void	paint_cloud_and_grass(t_setting *set)
{
	int	x;
	int	y;
	char *test;

	x = 0;
	while (x < WIDTH)   // 480
	{
		y = 0;
		while (y < HEIGHT)  // 680
		{
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

int	close_win(t_setting *set)
{
	int	i;

	i = -1;
	mlx_clear_window(set->mlx->mlx_init, set->mlx->mlx_window);
	mlx_destroy_image (set->mlx->mlx_init, set->mlx->mlx_img);
	mlx_destroy_window(set->mlx->mlx_init, set->mlx->mlx_window);
	while (set->map->map[++i])
		free (set->map->map[i]);
	
	ft_free_str(set);
/*	free_images (set); devamında
	if (set->map->north->image)
		free (set->map->north->path);
	if (set->map->south->image)
		free (set->map->south->path);
	if (set->map->west->image)
		free (set->map->west->path);
	if (set->map->east->image)
		free (set->map->east->path);   ÇOK LEAKS ALIYOR, BAKMAK LAZIM*/
	
	exit(0);
}
