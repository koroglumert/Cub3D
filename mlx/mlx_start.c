/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:54:02 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/20 23:00:22 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_mlx(t_mlx *mlx)
{
	mlx->mlx_init = mlx_init();
	mlx->mlx_window = mlx_new_window(mlx->mlx_init, WIDTH, HEIGHT, "cub3d");
	mlx->mlx_img = mlx_new_image(mlx->mlx_init, WIDTH, HEIGHT);
	mlx->mlx_img_addr = mlx_get_data_addr(mlx->mlx_img, 
		&mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);	
}

void	ft_images_management(t_mlx *mlx, t_map *map)
{
	
	map->north.image = mlx_xpm_file_to_image(mlx->mlx_init, map->north_text, &(map->north.img_w), &(map->north.img_h));
	map->south.image = mlx_xpm_file_to_image(mlx->mlx_init, map->south_text, &(map->south.img_w), &(map->south.img_h));
	map->west.image = mlx_xpm_file_to_image(mlx->mlx_init, map->west_text, &(map->west.img_w), &(map->west.img_h));
	map->east.image = mlx_xpm_file_to_image(mlx->mlx_init, map->east_text, &(map->east.img_w), &(map->east.img_h));
	if (!map->north.image || !map->south.image || !map->west.image || !map->east.image)
	{
		printf("texture error!\n");
		exit (1);
	}
	map->north.data = mlx_get_data_addr(map->north.image, &(map->north.bpp), &(map->north.sizeline), &(map->north.endian));
	map->south.data = mlx_get_data_addr(map->south.image, &(map->south.bpp), &(map->south.sizeline), &(map->south.endian));
	map->west.data = mlx_get_data_addr(map->west.image, &(map->west.bpp), &(map->west.sizeline), &(map->west.endian));
	map->east.data = mlx_get_data_addr(map->east.image, &(map->east.bpp), &(map->east.sizeline), &(map->east.endian));
}

void	mlx_start(t_setting *set)
{
	ft_init_mlx(set->mlx);
	ft_images_management(set->mlx, set->map);
	mlx_hook(set->mlx->mlx_window, 2, 1L << 0, &press_key, set);
	mlx_hook(set->mlx->mlx_window, 3, 1L << 0, &release_key, set);
	mlx_hook(set->mlx->mlx_window, 17, 0, close_win, set);
	//mlx_loop_hook(set->mlx->mlx_init, my_screen, set);
	my_screen(set);
	mlx_loop(set->mlx->mlx_init); //MERT KENDİME: Tuşa basılı tutulduğu sürekliliği sağlamak için loop'a almak gerekebilir.
}
