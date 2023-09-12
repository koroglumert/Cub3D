/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:04:14 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/12 03:35:20 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	control_xpm(char *str)
{
	int	len;
	len = ft_strlen(str);
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
	set->mlx->mlx_window = mlx_new_window(set->mlx->mlx_init, set->map->win_j, set->map->win_i, "cub3d");
	set->mlx->mlx_img = mlx_new_image(set->mlx->mlx_init, set->map->win_j, set->map->win_i);
	set->mlx->mlx_img_addr = mlx_get_data_addr(set->mlx->mlx_img, 
		&set->mlx->bits_per_pixel, &set->mlx->size_line, &set->mlx->endian);
	set->map->north.image = mlx_xpm_file_to_image(set->mlx->mlx_init, set->map->north_text, &(set->map->north.img_w), &(set->map->north.img_h));
	set->map->south.image = mlx_xpm_file_to_image(set->mlx->mlx_init, set->map->south_text, &(set->map->south.img_w), &(set->map->south.img_h));
	set->map->west.image = mlx_xpm_file_to_image(set->mlx->mlx_init, set->map->west_text, &(set->map->west.img_w), &(set->map->west.img_h));
	set->map->east.image = mlx_xpm_file_to_image(set->mlx->mlx_init, set->map->east_text, &(set->map->east.img_w), &(set->map->east.img_h));
	if (!set->map->north.image || !set->map->south.image || !set->map->west.image || !set->map->east.image)
	{
		printf("texture error!\n");
		exit (1);
	}
	set->map->north.data = mlx_get_data_addr(set->map->north.image, &(set->map->north.bpp), &(set->map->north.sizeline), &(set->map->north.endian));
	set->map->south.data = mlx_get_data_addr(set->map->south.image, &(set->map->south.bpp), &(set->map->south.sizeline), &(set->map->south.endian));
	set->map->west.data = mlx_get_data_addr(set->map->west.image, &(set->map->west.bpp), &(set->map->west.sizeline), &(set->map->west.endian));
	set->map->east.data = mlx_get_data_addr(set->map->east.image, &(set->map->east.bpp), &(set->map->east.sizeline), &(set->map->east.endian));	
}
