/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:54:02 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/27 18:22:57 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	paint_cloud_and_grass(t_setting *set)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				set->mlx->mlx_img_addr[y * WIDTH + x]
					= (int)set->map->rgb_ceiling;
			else
				set->mlx->mlx_img_addr[y * WIDTH + x]
					= (int)set->map->rgb_floor;
			y++;
		}
		x++;
	}
}

int	my_screen(t_setting *set)
{
	paint_cloud_and_grass(set);
	check_keys(set);
	ray_casting(set);
	mlx_put_image_to_window(set->mlx->mlx_init,
		set->mlx->mlx_window, set->mlx->mlx_img, 0, 0);
	return (0);
}

void	ft_images_management(t_mlx *mlx, t_map *map)
{
	map->south.image = mlx_xpm_file_to_image(mlx->mlx_init, map->south_text,
			&(map->south.img_w), &(map->south.img_h));
	map->north.image = mlx_xpm_file_to_image(mlx->mlx_init, map->north_text,
			&(map->north.img_w), &(map->north.img_h));
	map->west.image = mlx_xpm_file_to_image(mlx->mlx_init, map->west_text,
			&(map->west.img_w), &(map->west.img_h));
	map->east.image = mlx_xpm_file_to_image(mlx->mlx_init, map->east_text,
			&(map->east.img_w), &(map->east.img_h));
	if (!map->north.image || !map->south.image
		|| !map->west.image || !map->east.image)
	{
		printf("Error\ntexture error!\n");
		exit (1);
	}
	map->north.data = mlx_get_data_addr(map->north.image, &(map->north.bpp),
			&(map->north.sizeline), &(map->north.endian));
	map->south.data = mlx_get_data_addr(map->south.image, &(map->south.bpp),
			&(map->south.sizeline), &(map->south.endian));
	map->west.data = mlx_get_data_addr(map->west.image, &(map->west.bpp),
			&(map->west.sizeline), &(map->west.endian));
	map->east.data = mlx_get_data_addr(map->east.image, &(map->east.bpp),
			&(map->east.sizeline), &(map->east.endian));
}

void	ft_init_mlx(t_mlx *mlx)
{
	mlx->mlx_init = mlx_init();
	mlx->mlx_window = mlx_new_window(mlx->mlx_init, WIDTH, HEIGHT, "cub3D");
	mlx->mlx_img = mlx_new_image(mlx->mlx_init, WIDTH, HEIGHT);
	mlx->mlx_img_addr = (int *)mlx_get_data_addr(mlx->mlx_img,
			&mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
}

void	mlx_start(t_setting *set)
{
	ft_init_mlx(set->mlx);
	ft_images_management(set->mlx, set->map);
	mlx_hook(set->mlx->mlx_window, 2, 1L << 0, &press_key, set);
	mlx_hook(set->mlx->mlx_window, 3, 1L << 0, &release_key, set);
	mlx_hook(set->mlx->mlx_window, 17, 0, close_win, set);
	mlx_loop_hook(set->mlx->mlx_init, &my_screen, set);
	mlx_loop(set->mlx->mlx_init);
}
