/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:04:14 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/08 06:07:30 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	control_xpm(char *str)
{
	int	len;
	len = ft_strlen(str);
	printf("len:%d  str:%s\n", len, str);
	if (len < 4)
	{
		printf("wrong path\n");
		exit (1);
	}
	if (str[len - 1] != 'm' || str[len - 2] != 'p' || str[len - 3] != 'x' || str[len - 4] != '.')
	{
		printf("extension error '.xpm'\n");
		exit (1);
	}
}

void	textures_name_controller(t_map *map)
{
	control_xpm(map->east_text);
	control_xpm(map->south_text);
	control_xpm(map->west_text);
	control_xpm(map->north_text);
}

void	xpm_controller(t_map *map)
{
	int	*fd;
	int	i;
	textures_name_controller (map);
	i = 0;
	fd = malloc(sizeof(int) * 4);
	fd[0] = open(map->north_text, O_RDONLY);
	fd[1] = open(map->south_text, O_RDONLY);
	fd[2] = open(map->west_text, O_RDONLY);
	fd[3] = open(map->east_text, O_RDONLY);
	while (i < 4)
	{
		if (fd[i] == -1)
		{
			printf("textures not found\n");
			free (fd);
			exit (1);
		}
		i++;
	}
	free(fd);
}

void	put_images(t_setting *set)
{
	set->mlx->mlx_init = mlx_init();
	set->mlx->mlx_window = mlx_new_window(set->mlx->mlx_init, 800, 600, "cub3d");
	set->mlx->mlx_img = mlx_new_image(set->mlx->mlx_init, 800, 600);
	set->mlx->mlx_img_addr = mlx_get_data_addr(set->mlx->mlx_img, 
		&set->mlx->bits_per_pixel, &set->mlx->size_line, &set->mlx->endian);
	set->map->north->image = mlx_xpm_file_to_image(set->mlx->mlx_init, set->map->north_text, &(set->map->img_w), &(set->map->img_h));
	set->map->south->image = mlx_xpm_file_to_image(set->mlx->mlx_init, set->map->south_text, &(set->map->img_w), &(set->map->img_h));
	set->map->west->image = mlx_xpm_file_to_image(set->mlx->mlx_init, set->map->west_text, &(set->map->img_w), &(set->map->img_h));
	set->map->east->image = mlx_xpm_file_to_image(set->mlx->mlx_init, set->map->east_text, &(set->map->img_w), &(set->map->img_h));
	if (!set->map->north->image || !set->map->south->image || !set->map->west->image || !set->map->east->image)
	{
		printf("texture error!\n");
		exit (1);
	}
	set->map->north->data = mlx_get_data_addr(set->map->north->image, &(set->map->north->bpp), &(set->map->north->sizeline), &(set->map->north->endian));
	set->map->south->data = mlx_get_data_addr(set->map->south->image, &(set->map->south->bpp), &(set->map->south->sizeline), &(set->map->south->endian));
	set->map->west->data = mlx_get_data_addr(set->map->west->image, &(set->map->west->bpp), &(set->map->west->sizeline), &(set->map->west->endian));
	set->map->east->data = mlx_get_data_addr(set->map->east->image, &(set->map->east->bpp), &(set->map->east->sizeline), &(set->map->east->endian));	
}

void	player_coordinate (t_setting *set)
{
	set->player->x = (double)(set->map->ply_x) + 0.5;
	set->player->y = (double)(set->map->ply_y) + 0.5;
}

int	press_key (int	keycode, t_setting *set)
{
	set->move_speed = 0.05;
	set->rot_speed = 0.05;
	if (keycode == 13)
		set->press_w = 1;
	else if (keycode == 0)
		set->press_a = 1;
	else if (keycode == 1)
		set->press_s = 1;
	else if (keycode == 2)
		set->press_d = 1;
//	else if (keycode == 53)	--- ESC
	/* 
	----directions--- öncesine handle_direct diye fonk yazmıslar
	else if (keycode == 124)
		turn_right(set);
	else if (keycode == 123)
		turn_left(set);
	*/
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
	return (0);
}

void	take_rgb_f_c(t_setting *set)
{
	set->map->rgb_ceiling = (set->map->rgb_c[0] << 16) 
		+ (set->map->rgb_c[1] << 8) + set->map->rgb_c[2];
	set->map->rgb_floor = (set->map->rgb_f[0] << 16) 
		+ (set->map->rgb_f[1] << 8) + set->map->rgb_f[2];
}

void	paint_cloud_and_grass(t_setting *set)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 800)
	{
		j = -1;
		while (++j < 600)
		{
			if (j < set->map->win_j / 2)
			{
				set->mlx->mlx_img_addr[j * 600 + i] 
					= set->map->rgb_ceiling;
			}
			else
			{
				set->mlx->mlx_img_addr[j * 800 + i]
					= set->map->rgb_floor;
			}
		}
	}
}

int	my_screen(t_setting *set)
{
	mlx_destroy_image (set->mlx->mlx_init, set->mlx->mlx_img);
	set->mlx->mlx_img = mlx_new_image(set->mlx->mlx_init, 800, 600);
	set->mlx->mlx_img_addr = mlx_get_data_addr(set->mlx->mlx_img, 
		&set->mlx->bits_per_pixel, &set->mlx->size_line, &set->mlx->endian);
	paint_cloud_and_grass(set);
	return (0);
}

void	start_mlx(t_setting *set)
{
	take_rgb_f_c(set);
	xpm_controller (set->map);
	put_images(set);
//	player_coordinate(set);  // NEDEN
	mlx_hook(set->mlx->mlx_window, 2, 1L << 0, &press_key, set);
	mlx_hook(set->mlx->mlx_window, 3, 1L << 0, &release_key, set);
/* mlx_loop_hook ile ilgili bilgi:Örneğin, eğer bir uygulama 60 FPS (Frame Per Second) ile çalışıyorsa, 
mlx_loop_hook ile belirtilen işlev her saniyede 60 kez çağrılacaktır. Bu, düzenli bir animasyon veya 
grafik güncellemesi için uygun bir hızdır. Ancak, bu hız uygulama ve donanım özelliklerine göre değişebilir. (YUHHH)*/
	mlx_loop_hook(set->mlx->mlx_init, &my_screen, set);
//	mlx_hook (set->mlx->mlx_window, 17, 0, close, set); ÇARPI BUTONU İÇİN FONKSİYON YAZMAK GEREK
	mlx_loop(set->mlx->mlx_init);
}
