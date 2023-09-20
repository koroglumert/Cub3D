/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:50:52 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/20 03:31:39 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	my_screen(t_setting *set)
{
	mlx_destroy_image (set->mlx->mlx_init, set->mlx->mlx_img); //MERT: neden destroy ettik 
	set->mlx->mlx_img = mlx_new_image(set->mlx->mlx_init, WIDTH, HEIGHT);
	/*set->mlx->mlx_img_addr = mlx_get_data_addr(set->mlx->mlx_img, 
		&set->mlx->bits_per_pixel, &set->mlx->size_line, &set->mlx->endian);*/
	
	printf("M\n");
	fflush(stdout);
	ray_casting(set); //MERT KENDİME: Burası tuşa bağlı konumda düzenlemeyi sağlayacak yer
	printf("N\n");
	fflush(stdout);
	check_keys(set); //MERT KENDİME: Check keys mi ray casting mi önde olmalı?
	
	mlx_clear_window(set->mlx->mlx_init, set->mlx->mlx_window);
	
	paint_cloud_and_grass(set); //MERT KENDİME: Burası ekrana baskıyı sağlayacak yer, sıfırdan kodlamam lazım
	return (0);
}

int	close_win(t_setting *set)
{
	int	i;

	i = -1;
	mlx_clear_window(set->mlx->mlx_init, set->mlx->mlx_window);
	mlx_destroy_image (set->mlx->mlx_init, set->mlx->mlx_img);
	mlx_destroy_window(set->mlx->mlx_init, set->mlx->mlx_window);
	while (set->map->map[++i])
		free (set->map->map[i]);
	ft_free_str(set);
/*	free_images (set); devamında
	if (set->map->north->image)
		free (set->map->north->path);
	if (set->map->south->image)
		free (set->map->south->path);
	if (set->map->west->image)
		free (set->map->west->path);
	if (set->map->east->image)
		free (set->map->east->path);   ÇOK LEAKS ALIYOR, BAKMAK LAZIM*/
	
	exit(0);
}

int	press_key (int	keycode, t_setting *set)
{
	set->move_speed = 0.05;
	set->rot_speed = 0.05;
	if (keycode == W)
		set->press_w = 1; //go right çağır
	else if (keycode == A)
		set->press_a = 1;
	else if (keycode == S)
		set->press_s = 1;
	else if (keycode == D)
		set->press_d = 1;
	else if (keycode == ESC)
		exit (close_win(set));
	else if (keycode == RIGHT)
		set->direct_right = 1;
	else if (keycode == LEFT)
		set->direct_left = 1;
	else
		return (0);
	printf("P\n");
	fflush(stdout);
	my_screen(set);
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
	printf("R\n");
	fflush(stdout);
	//my_screen(set);
	return (1);
}
