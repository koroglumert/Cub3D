/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:34 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/26 12:03:02 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_oh_my_walls(t_rc *rc)
{
	if (rc->face_of_cube == 'x')
		rc->distance = rc->sidedist_x - rc->deltadist_x;
	else
		rc->distance = rc->sidedist_y - rc->deltadist_y;
	if (rc->distance <= 0)
		rc->distance = 0.7;
	rc->wall_height = (int)(HEIGHT / rc->distance);
	rc->beginning_of_the_walls = (HEIGHT / 2) - (rc->wall_height / 2);
	if (rc->beginning_of_the_walls < 0)
		rc->beginning_of_the_walls = 0;
	rc->end_of_the_walls = (HEIGHT / 2) + (rc->wall_height / 2);
	if (rc->end_of_the_walls >= HEIGHT)
		rc->end_of_the_walls = HEIGHT - 1;
}

static void	ft_dda(t_rc *rc, t_map *map)
{
	while (1)
	{
		if (rc->sidedist_x < rc->sidedist_y)
		{
			rc->sidedist_x += rc->deltadist_x;
			rc->map_x += rc->move_x;
			rc->face_of_cube = 'x';
		}
		else
		{
			rc->sidedist_y += rc->deltadist_y;
			rc->map_y += rc->move_y;
			rc->face_of_cube = 'y';
		}
		if (map->map[rc->map_y][rc->map_x] == '1')
			break ;
	}
}

static void	ft_take_step_and_sidedist(t_rc	*rc)
{
	if (rc->raydir_x < 0)
	{
		rc->move_x = -1;
		rc->sidedist_x = (rc->pos_x - rc->map_x)
			* rc->deltadist_x;
	}
	else
	{
		rc->move_x = 1;
		rc->sidedist_x = (1.0 + rc->map_x - rc->pos_x)
			* rc->deltadist_x;
	}
	if (rc->raydir_y < 0)
	{
		rc->move_y = -1;
		rc->sidedist_y = (rc->pos_y - rc->map_y)
			* rc->deltadist_y;
	}
	else
	{
		rc->move_y = 1;
		rc->sidedist_y = (1.0 + rc->map_y - rc->pos_y)
			* rc->deltadist_y;
	}
}

void	ray_casting(t_setting *set)
{
	t_rc	*rc;
	int		x;

	x = 0;
	rc = set->rc;
	while (x < WIDTH)
	{
		rc->camera_x = (2 * x / (double)WIDTH - 1);
		rc->raydir_x = rc->dir_x + rc->plane_x * rc->camera_x ;
		rc->raydir_y = rc->dir_y + rc->plane_y * rc->camera_x ;
		rc->map_x = rc->pos_x;
		rc->map_y = rc->pos_y;
		rc->deltadist_x = fabs(1 / rc->raydir_x);
		rc->deltadist_y = fabs(1 / rc->raydir_y);
		ft_take_step_and_sidedist(set->rc);
		ft_dda(set->rc, set->map);
		ft_oh_my_walls(set->rc);
		ft_get_images(set, set->rc, x);
		x++;
	}
}
