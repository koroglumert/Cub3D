/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:50:52 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/23 13:22:55 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_key(int keycode, t_setting *set)
{
	if (keycode == W)
		set->press_w = 1;
	else if (keycode == A)
		set->press_a = 1;
	else if (keycode == S)
		set->press_s = 1;
	else if (keycode == D)
		set->press_d = 1;
	else if (keycode == ESC)
		close_win(set);
	else if (keycode == RIGHT)
		set->direct_right = 1;
	else if (keycode == LEFT)
		set->direct_left = 1;
	else
		return (0);
	return (1);
}

int	release_key(int keycode, t_setting *set)
{
	if (keycode == W)
		set->press_w = 0;
	else if (keycode == A)
		set->press_a = 0;
	else if (keycode == S)
		set->press_s = 0;
	else if (keycode == D)
		set->press_d = 0;
	else if (keycode == RIGHT)
		set->direct_right = 0;
	else if (keycode == LEFT)
		set->direct_left = 0;
	else
		return (0);
	return (1);
}

int	close_win(t_setting *set)
{
	mlx_clear_window(set->mlx->mlx_init, set->mlx->mlx_window);
	mlx_destroy_image (set->mlx->mlx_init, set->mlx->mlx_img);
	mlx_destroy_image (set->mlx->mlx_init, set->map->south.image);
	mlx_destroy_image (set->mlx->mlx_init, set->map->north.image);
	mlx_destroy_image (set->mlx->mlx_init, set->map->west.image);
	mlx_destroy_image (set->mlx->mlx_init, set->map->east.image);
	mlx_destroy_window(set->mlx->mlx_init, set->mlx->mlx_window);
	exit(0);
}
