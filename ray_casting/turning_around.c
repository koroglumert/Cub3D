/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turning_around.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:10:02 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/26 12:02:49 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	turn_left(t_setting *set)
{
	t_rc	*rc;
	double	old_dir_x;
	double	old_plane_x;
	double	rs;

	rc = set->rc;
	rs = set->rot_speed / 2;
	old_dir_x = set->rc->dir_x;
	old_plane_x = set->rc->plane_x;
	rc->dir_x = old_dir_x * cos(rs) - rc->dir_y * sin(rs);
	rc->dir_y = old_dir_x * sin(rs) + rc->dir_y * cos(rs);
	rc->plane_x = old_plane_x * cos(rs) - rc->plane_y * sin(rs);
	rc->plane_y = old_plane_x * sin(rs) + rc->plane_y * cos(rs);
}

static void	turn_right(t_setting *set)
{
	t_rc	*rc;
	double	old_dir_x;
	double	old_plane_x;
	double	rs;

	rc = set->rc;
	rs = set->rot_speed / 2;
	old_dir_x = rc->dir_x;
	old_plane_x = rc->plane_x;
	rc->dir_x = old_dir_x * cos(-rs) - rc->dir_y * sin(-rs);
	rc->dir_y = old_dir_x * sin(-rs) + rc->dir_y * cos(-rs);
	rc->plane_x = old_plane_x * cos(-rs) - rc->plane_y * sin(-rs);
	rc->plane_y = old_plane_x * sin(-rs) + rc->plane_y * cos(-rs);
}

static void	go_a_d(t_setting *set, double spd)
{
	t_rc	*rc;
	double	x;
	double	y;

	rc = set->rc;
	y = rc->pos_y;
	x = rc->pos_x;
	if (set->press_a == 1 && set->map->map[(int)(y - rc->plane_y * spd)]
		[(int)(x - rc->plane_x * spd)] != '1')
	{
		rc->pos_x -= rc->plane_x * spd;
		rc->pos_y -= rc->plane_y * spd;
	}
	if (set->press_d == 1 && set->map->map[(int)(y + rc->plane_y * spd)]
		[(int)(x + rc->plane_x * spd)] != '1')
	{
		rc->pos_x += rc->plane_x * spd;
		rc->pos_y += rc->plane_y * spd;
	}
}

static void	go_w_s(t_setting *set, double spd)
{
	t_rc	*rc;
	double	x;
	double	y;

	rc = set->rc;
	y = rc->pos_y;
	x = rc->pos_x;
	if (set->press_w == 1 && set->map->map[(int)(y + rc->dir_y * spd)]
		[(int)(x + rc->dir_x * spd)] != '1')
	{
		rc->pos_x += rc->dir_x * spd;
		rc->pos_y += rc->dir_y * spd;
	}
	if (set->press_s == 1 && set->map->map[(int)(y - rc->dir_y * spd)]
		[(int)(x - rc->dir_x * spd)] != '1')
	{
		rc->pos_x -= rc->dir_x * spd;
		rc->pos_y -= rc->dir_y * spd;
	}
}

void	check_keys(t_setting *set)
{
	if (set->press_w == 1 || set->press_s == 1)
		go_w_s(set, set->move_speed);
	if (set->press_a == 1 || set->press_d == 1)
		go_a_d(set, set->move_speed);
	if (set->direct_right == 1)
	{
		if (set->rc->start_position == 'N'
			|| set->rc->start_position == 'S')
			turn_right(set);
		else
			turn_left(set);
	}
	if (set->direct_left == 1)
	{
		if (set->rc->start_position == 'N'
			|| set->rc->start_position == 'S')
			turn_left(set);
		else
			turn_right(set);
	}
}
