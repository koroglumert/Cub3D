/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 21:04:14 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/19 22:28:18 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	control_xpm(char *str)
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

static void	textures_name_controller(t_map *map)
{
	control_xpm(map->east_text);
	control_xpm(map->south_text);
	control_xpm(map->west_text);
	control_xpm(map->north_text);
}

void	ft_check_xpm(t_map *map)
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
