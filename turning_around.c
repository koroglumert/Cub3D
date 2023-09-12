/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turning_around.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:10:02 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/11 21:49:44 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_right(t_setting *set)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rs;

	rs = set->player->rot_speed;
	old_dir_x = set->player->dir_x;
	old_plane_x = set->player->plane_x;
	
	set->player->dir_x = old_dir_x * cos(-rs) - set->player->dir_y * sin(-rs);
	set->player->dir_y = old_dir_x * sin(-rs) + set->player->dir_y * cos(-rs);
	set->player->plane_x = old_plane_x * cos(-rs) - set->player->plane_y * sin(-rs);
	set->player->plane_y = old_plane_x * sin(-rs) + set->player->plane_y * cos(-rs);
}

void	turn_left(t_setting *set)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rs;

	rs = set->player->rot_speed;
	old_dir_x = set->player->dir_x;
	old_plane_x = set->player->plane_x;
	
	set->player->dir_x = old_dir_x * cos(rs) - set->player->dir_y * sin(rs);
	set->player->dir_y = old_dir_x * sin(rs) + set->player->dir_y * cos(rs);
	set->player->plane_x = old_plane_x * cos(rs) - set->player->plane_y * sin(rs);
	set->player->plane_y = old_plane_x * sin(rs) + set->player->plane_y * cos(rs);	
}

void	go_up(t_setting *set)
{
	int		x;
	int		y;
	double	spd;

	spd = set->player->move_speed;
	y = set->player->ply_j;
	x = set->player->ply_i;
	if (set->map->map[(int)(y + set->player->dir_x * spd)][x] == '0')
		set->player->ply_j += set->player->dir_x * spd;
	if (set->map->map[y][(int)(x + set->player->dir_x * spd)] == '0')
		set->player->ply_i += set->player->dir_y * spd;
}

void	go_down(t_setting *set)
{
	int		x;
	int		y;
	double	spd;

	spd = set->player->move_speed;
	y = set->player->ply_j;
	x = set->player->ply_i;
	if (set->map->map[(int)(y - set->player->dir_x * spd)][x] == '0')
		set->player->ply_j -= set->player->dir_x * spd;
	if (set->map->map[y][(int)(x - set->player->dir_x * spd)] == '0')
		set->player->ply_i -= set->player->dir_y * spd;
}

void	eescape(t_setting *set)
{
	(void)set;
	exit(0);
}
