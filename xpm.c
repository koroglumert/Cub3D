/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:04:14 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/05 21:45:58 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	control_xpm(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if (str[len] != 'm' || str[len - 1] != 'p' || str[len - 2] != 'x' || str[len - 3] != '.')
	{
		printf("extension error '.xpm'\n");
		exit (1);
	}
}

void	textures_name_controller(t_map *map)
{
	control_xpm(map->north_text);
	control_xpm(map->east_text);
	control_xpm(map->south_text);
	control_xpm(map->west_text);
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

void	start_mlx(t_setting *set)
{
	xpm_controller (set->map);
	set->mlx->mlx_init = mlx_init();
	set->mlx->mlx_window = mlx_new_window(set->mlx->mlx_init, 800, 600, "cub3d");
//	set->mlx->img_e = mlx_xpm_to_image(set->mlx->mlx_init, "textures/  .xpm",  )
//	set->mlx->img_w = mlx_xpm_to_image(set->mlx->mlx_init, "textures/  .xpm",  )
//	set->mlx->img_s = mlx_xpm_to_image(set->mlx->mlx_init, "textures/  .xpm",  )
//	set->mlx->img_n = mlx_xpm_to_image(set->mlx->mlx_init, "textures/  .xpm",  )

/* image struct ı oluşturmak lazım her bir img için		BEN MLXİ UNUTMUSUM
	
	void	*window;
	int		*image;
	char	*data;
	int		bpp; 
	int		sizeline;
	int		endian; 

*/
}
