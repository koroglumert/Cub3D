/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turning_around.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:10:02 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/22 23:56:45 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	turn_right(t_setting *set)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rs;

	rs = set->rot_speed;
	old_dir_x = set->player->dir_x;
	old_plane_x = set->player->plane_x;
	
	set->player->dir_x = old_dir_x * cos(-rs) - set->player->dir_y * sin(-rs);
	set->player->dir_y = old_dir_x * sin(-rs) + set->player->dir_y * cos(-rs);
	set->player->plane_x = old_plane_x * cos(-rs) - set->player->plane_y * sin(-rs);
	set->player->plane_y = old_plane_x * sin(-rs) + set->player->plane_y * cos(-rs);
}

static void	turn_left(t_setting *set)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rs;

	rs = set->rot_speed;
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
	spd = set->move_speed;
	printf("sdp = %f\n", set->player->dir_x);
	y = set->player->pos_y;
	x = set->player->pos_x;
	if (set->map->map[y + (int)(set->player->dir_y * spd)][x + (int)(set->player->dir_x * spd)] != '1')
	{
		
		set->player->pos_x += set->player->dir_x * spd;
		set->player->pos_y += set->player->dir_y * spd;
		
	}
	
}

static void	go_down(t_setting *set)
{
	int		x;
	int		y;
	double	spd;

	spd = set->move_speed;
	y = set->player->pos_y;
	x = set->player->pos_x;
	if (set->map->map[(int)(y - set->player->dir_x * spd)][x] == '0')
		set->player->pos_x -= (int)(set->player->dir_x * spd);
	if (set->map->map[y][(int)(x - set->player->dir_x * spd)] == '0')
		set->player->pos_y -= (int)(set->player->dir_y * spd);
}
/*
void	eescape(t_setting *set)
{
	(void)set;
	exit(0);
}
*/

void	check_keys(t_setting *set) // eksik tuşlar
{
	if(set->press_w == 1)
		go_up(set);
	if (set->press_s == 1)
		go_down (set);
	if (set->direct_right == 1)
		turn_right (set);
	if (set->direct_left == 1)
		turn_left (set);
}
