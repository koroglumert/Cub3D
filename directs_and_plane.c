/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directs_and_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:34 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/10 11:52:00 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	take_first_directs(t_setting *set)
{
	set->player->dir_x = 0.0;
	set->player->dir_y = 0.0; 
	if (set->map->map[set->player->ply_i][set->player->ply_j] == 'N')
		set->player->dir_y = 1.0; 
	else if (set->map->map[set->player->ply_i][set->player->ply_j] == 'S')
		set->player->dir_y = -1.0; 		
	else if (set->map->map[set->player->ply_i][set->player->ply_j] == 'E')
		set->player->dir_x = 1.0;
	else if (set->map->map[set->player->ply_i][set->player->ply_j] == 'W')
		set->player->dir_x = -1.0;
	return(0);
}

int	take_first_plane_coor(t_setting *set)
{
	set->player->plane_x = 0;
	set->player->plane_y = 0;
	if (set->map->map[set->player->ply_i][set->player->ply_j] == 'N')
		set->player->plane_y = 0.66;
	else if (set->map->map[set->player->ply_i][set->player->ply_j] == 'S')
		set->player->plane_y = -0.66;
	else if (set->map->map[set->player->ply_i][set->player->ply_j] == 'E')
		set->player->plane_x = 0.66;
	else if (set->map->map[set->player->ply_i][set->player->ply_j] == 'W')
		set->player->plane_x = -0.66;
	return (0);
}

void	take_step_and_sidedist(t_setting *set) //benzer üçgenlerde uzunluk
{
	if (set->player->raydir_x < 0)
	{
		set->player->move_x = -1; 
		set->player->sidedist_x = (set->player->ply_j - set->player->x)
			* set->player->deltadist_x;
	}
	else
	{
		set->player->move_x = 1;
		set->player->sidedist_x = (set->player->x - set->player->ply_j)  // parantez içine +1 maybe
			* set->player->deltadist_x;
	}
	if (set->player->raydir_y < 0)
	{
		set->player->move_y = -1;
		set->player->sidedist_y = (set->player->ply_i - set->player->y)
			* set->player->deltadist_y;
	}
	else
	{
		set->player->move_y = 1;
		set->player->sidedist_y = (set->player->y - set->player->ply_j)  // +1 maybe
			* set->player->deltadist_y;
	}
}

void	dda(t_setting *set)
{
	int	is_it_wall;

	is_it_wall = 0;
	while (is_it_wall == 0)
	{
		if (set->player->sidedist_x < set->player->sidedist_y)
		{
			set->player->sidedist_x += set->player->deltadist_x;
			set->player->x += set->player->move_x;
			set->player->face_of_cube = 'x';
		}
		else
		{
			set->player->sidedist_y += set->player->deltadist_y;
			set->player->y += set->player->move_y;
			set->player->face_of_cube = 'y';
		}
		if (set->map->map[(int)set->player->y][(int)set->player->x] == '1')
			is_it_wall = 1;
	}
}

void	ray_casting (t_setting *set)
{
	int	j;

	j = 0;
	while (j < WIDTH)
	{
		set->player->camera_x = 2 * j / (double)set->map->win_j - 1;
		set->player->raydir_x = set->player->dir_x + set->player->plane_x * set->player->camera_x;
		set->player->raydir_y = set->player->dir_y + set->player->plane_y * set->player->camera_y;
		set->player->x = set->player->ply_j;
		set->player->y = set->player->ply_i;
		set->player->deltadist_x = fabs(1 / set->player->raydir_x);
		set->player->deltadist_y = fabs(1 / set->player->raydir_y);
		take_step_and_sidedist(set);
		dda(set);
		oh_my_walls(set);
		get_images(set, j);
		j++;
	}
}
