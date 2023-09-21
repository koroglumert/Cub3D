/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directs_and_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:34 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/20 23:00:32 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_oh_my_walls(t_player *player)
{
	if (player->face_of_cube == 'x')
		player->distance = player->sidedist_x - player->deltadist_x;
	else
		player->distance = player->sidedist_y - player->deltadist_y;   //dik uzaklık olmadı bence bunlar ama neyse
	player->wall_height = HEIGHT / player->distance;
	player->beginning_of_the_walls = HEIGHT / 2 - player->wall_height / 2;
	if (player->beginning_of_the_walls < 0)  // duvara çok yakın (dibinde) olma ihtimalimiz
		player->beginning_of_the_walls = 0;
	player->end_of_the_walls = HEIGHT / 2 + player->wall_height / 2;
	if (player->end_of_the_walls >= HEIGHT)
		player->end_of_the_walls = HEIGHT - 1;
//	printf("%d   dist:%f  wall:%d  %d   %d\n", HEIGHT, set->player->distance, set->player->wall_height, set->player->beginning_of_the_walls, set->player->end_of_the_walls);
}

static void	ft_dda(t_player *player, t_map *map, int j)
{
	int	is_it_wall;

	is_it_wall = 0;
	while (is_it_wall == 0)
	{
		if (player->sidedist_x < player->sidedist_y)
		{
			player->sidedist_x += player->deltadist_x;
			player->x += player->move_x;
			player->face_of_cube = 'x';
		}
		else
		{
			player->sidedist_y += player->deltadist_y;
			player->y += player->move_y;
			player->face_of_cube = 'y';
		}
		if (map->map[(int)player->y][(int)player->x] == '1')
			is_it_wall = 1;
		
	}
	(void)j;
}

static void	ft_take_step_and_sidedist(t_player	*player) //benzer üçgenlerde uzunluk
{
	if (player->raydir_x < 0)
	{
		player->move_x = -1; 
		player->sidedist_x = (player->ply_j - player->x)
			* player->deltadist_x;
	}
	else
	{
		player->move_x = 1;
		player->sidedist_x = (1 + player->x - player->ply_j)  // parantez içine +1 maybe
			* player->deltadist_x;
	}
	if (player->raydir_y < 0)
	{
		player->move_y = -1;
		player->sidedist_y = (player->ply_i - player->y)
			* player->deltadist_y;
	}
	else
	{
		player->move_y = 1;
		player->sidedist_y = (player->y - player->ply_j)  // +1 maybe
			* player->deltadist_y;
	}
}

void	ray_casting (t_setting *set)
{
	t_player	*player;
	int			j;

	j = 0;
	player = set->player;
	while (j < WIDTH)
	{
		
		player->camera_x = 2 * j / (double)WIDTH - 1;
		player->raydir_x = player->dir_x + player->plane_x * player->camera_x;
		player->raydir_y = player->dir_y + player->plane_y * player->camera_x;
	//	printf("player->raydir_x:%f   player->raydir_y:%f\n", player->raydir_x,player->raydir_y);

		player->x = (double)(player->ply_j);
		player->y = (double)(player->ply_i);
		player->deltadist_x = fabs(1 / player->raydir_x);
		player->deltadist_y = fabs(1 / player->raydir_y);
		ft_take_step_and_sidedist(set->player);
		
		ft_dda(set->player, set->map, j);

		ft_oh_my_walls(set->player);

		ft_get_images(set, set->player, j);
		
		j++;
	}
}
