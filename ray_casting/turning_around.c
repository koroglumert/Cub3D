/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turning_around.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:10:02 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/23 16:26:03 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	turn_left(t_setting *set)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;
	double		rs;

	player = set->player;
	rs = set->rot_speed / 2;
	old_dir_x = set->player->dir_x;
	old_plane_x = set->player->plane_x;
	player->dir_x = old_dir_x * cos(rs) - player->dir_y * sin(rs);
	player->dir_y = old_dir_x * sin(rs) + player->dir_y * cos(rs);
	player->plane_x = old_plane_x * cos(rs) - player->plane_y * sin(rs);
	player->plane_y = old_plane_x * sin(rs) + player->plane_y * cos(rs);
}

static void	turn_right(t_setting *set)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;
	double		rs;

	player = set->player;
	rs = set->rot_speed / 2;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = old_dir_x * cos(-rs) - player->dir_y * sin(-rs);
	player->dir_y = old_dir_x * sin(-rs) + player->dir_y * cos(-rs);
	player->plane_x = old_plane_x * cos(-rs) - player->plane_y * sin(-rs);
	player->plane_y = old_plane_x * sin(-rs) + player->plane_y * cos(-rs);
}

static void	go_a_d(t_setting *set, double spd)
{
	t_player	*player;
	double		x;
	double		y;

	player = set->player;
	y = player->pos_y;
	x = player->pos_x;
	if (set->press_a == 1 && set->map->map[(int)(y - player->plane_y * spd)]
		[(int)(x - player->plane_x * spd)] != '1')
	{
			player->pos_x -= player->plane_x * spd;
			player->pos_y -= player->plane_y * spd;
	}
	if (set->press_d == 1 && set->map->map[(int)(y + player->plane_y * spd)]
		[(int)(x + player->plane_x * spd)] != '1')
	{
		player->pos_x += player->plane_x * spd;
		player->pos_y += player->plane_y * spd;
	}
}

static void	go_w_s(t_setting *set, double spd)
{
	t_player	*player;
	double		x;
	double		y;

	player = set->player;
	y = player->pos_y;
	x = player->pos_x;
	if (set->press_w == 1 && set->map->map[(int)(y + player->dir_y * spd)]
		[(int)(x + player->dir_x * spd)] != '1')
	{
			player->pos_x += player->dir_x * spd;
			player->pos_y += player->dir_y * spd;
	}
	if (set->press_s == 1 && set->map->map[(int)(y - player->dir_y * spd)]
		[(int)(x - player->dir_x * spd)] != '1')
	{
		player->pos_x -= player->dir_x * spd;
		player->pos_y -= player->dir_y * spd;
	}
}

void	check_keys(t_setting *set)
{
	if(set->press_w == 1 || set->press_s == 1)
		go_w_s(set, set->move_speed);
	if(set->press_a == 1 || set->press_d == 1)
		go_a_d(set, set->move_speed);
	if (set->direct_right == 1)
		turn_right(set);
	if (set->direct_left == 1)
		turn_left(set);
}
