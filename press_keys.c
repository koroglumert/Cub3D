/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:50:52 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/12 12:08:55 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_key (int	keycode, t_setting *set)
{
	set->move_speed = 0.05;
	set->rot_speed = 0.05;
	if (keycode == 13)
		set->press_w = 1; //go right çağır
	else if (keycode == 0)
		set->press_a = 1;
	else if (keycode == 1)
		set->press_s = 1;
	else if (keycode == 2)
		set->press_d = 1;
	else if (keycode == 53)
		exit (close_win(set));
	else if (keycode == 124)
		set->direct_right = 1;
	else if (keycode == 123)
		set->direct_left = 1;
	
	return (0);
}

int	release_key(int keycode, t_setting *set)
{
	if (keycode == 13)
		set->press_w = 0;
	else if (keycode == 0)
		set->press_a = 0;
	else if (keycode == 1)
		set->press_s = 0;
	else if (keycode == 2)
		set->press_d = 0;
	else if (keycode == 124)
		set->direct_right = 0;
	else if (keycode == 123)
		set->direct_left = 0;
	return (0);
}
