/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directs_and_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:34 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/21 18:52:32 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_oh_my_walls(t_player *player)
{
	/*int pitch;
	
	pitch = 100;*/
	
	if (player->face_of_cube == 'x')
		player->distance = player->sidedist_x - player->deltadist_x;
	else
		player->distance = player->sidedist_y - player->deltadist_y;   //dik uzaklık olmadı bence bunlar ama neyse
	if (player->distance == 0)
		player->distance = 1e14;
	player->wall_height = (int)(HEIGHT / player->distance);

	player->beginning_of_the_walls = (HEIGHT / 2) - (player->wall_height / 2); // + pitch
	if (player->beginning_of_the_walls < 0)  // duvara çok yakın (dibinde) olma ihtimalimiz
		player->beginning_of_the_walls = 0;
	player->end_of_the_walls = (HEIGHT / 2) + (player->wall_height / 2); // + pitch
	if (player->end_of_the_walls >= HEIGHT)
		player->end_of_the_walls = HEIGHT - 1;
}

static void	ft_dda(t_player *player, t_map *map)
{
	while (1)
	{
		if (player->sidedist_x < player->sidedist_y)
		{
			player->sidedist_x += player->deltadist_x;
			player->map_x += player->move_x;
			player->face_of_cube = 'x';
		}
		else
		{
			player->sidedist_y += player->deltadist_y;
			player->map_y += player->move_y;
			player->face_of_cube = 'y';
		}
		if (map->map[player->map_y][player->map_x] == '1') //hata varsa doubleden kaynaklı
			break ;
	}
}

static void	ft_take_step_and_sidedist(t_player	*player) //benzer üçgenlerde uzunluk
{
	if (player->raydir_x < 0)
	{
		player->move_x = -1; 
		player->sidedist_x = (player->pos_x - player->map_x)
			* player->deltadist_x;
	}
	else
	{
		player->move_x = 1;
		player->sidedist_x = (1.0 + player->map_x - player->pos_x)
			* player->deltadist_x;
	}
	if (player->raydir_y < 0)
	{
		player->move_y = 1;
		player->sidedist_y = (player->pos_y - player->map_y)
			* player->deltadist_y;
	}
	else
	{
		player->move_y = 1;
		player->sidedist_y = (1.0 + player->map_y - player->pos_x)
			* player->deltadist_y;
	}
}

void	ray_casting (t_setting *set)
{
	t_player	*player;
	int			j;

	j = 0;
	player = set->player;
	//printf("\nplayer i = %d, playre j = %d\n", player->pos_y, player->pos_x);
	while (j < WIDTH)
	{
		player->camera_x = (2 * j / (double)WIDTH - 1);
		player->raydir_x = player->dir_x + player->plane_x * player->camera_x;
		player->raydir_y = player->dir_y + player->plane_y * player->camera_x; //camera_y yaptık
		player->map_x = (int)player->pos_x;
		player->map_y = (int)player->pos_y;
		if (player->raydir_x == 0)
			player->deltadist_x = 1e14;
		else
			player->deltadist_x = fabs(1 / player->raydir_x);
		if (player->raydir_y == 0)
			player->deltadist_y = 1e14;
		else
			player->deltadist_y = fabs(1 / player->raydir_y);
		ft_take_step_and_sidedist(set->player);
		ft_dda(set->player, set->map);
		ft_oh_my_walls(set->player);
		
		ft_get_images(set, set->player, j);
		
		j++;
	}
	printf("j = %d", j);
	
}
