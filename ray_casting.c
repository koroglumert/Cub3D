/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:54:02 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/12 12:25:55 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_screen(t_setting *set)
{
	mlx_destroy_image (set->mlx->mlx_init, set->mlx->mlx_img);
	set->mlx->mlx_img = mlx_new_image(set->mlx->mlx_init, WIDTH, HEIGHT);
	set->mlx->mlx_img_addr = mlx_get_data_addr(set->mlx->mlx_img, 
		&set->mlx->bits_per_pixel, &set->mlx->size_line, &set->mlx->endian);
	paint_cloud_and_grass(set);
	ray_casting(set);
	check_keys(set);
	return (0);
}

void	start_mlx(t_setting *set)
{
	put_images(set);
	take_first_directs(set);
	take_first_plane_coor(set);
	player_coordinate(set);  // NEDEN
	xpm_controller (set->map);
	take_rgb_f_c(set);
	mlx_loop_hook(set->mlx->mlx_init, &my_screen, set);
	mlx_hook(set->mlx->mlx_window, 2, 1L << 0, &press_key, set);
	mlx_hook(set->mlx->mlx_window, 3, 1L << 0, &release_key, set);
	mlx_hook (set->mlx->mlx_window, 17, 0, close_win, set); // çarpı butonu için
	mlx_loop(set->mlx->mlx_init);
}
