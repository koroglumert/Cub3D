/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:21 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/01 15:54:42 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_name(char *av1)
{
	int	i;

	i = ft_strlen(av1);
	if (i <= 4)
		return (1);
	i--;
	if (!(av1[i] == 'b' && av1[i - 1] == 'u' && av1[i - 2] == 'c' && av1[i - 3] == '.'))
		return (1);
	return (0);
}

int	check_if_them_full(t_map *map)
{
	if (map->north_text == NULL 
		|| map->south_text == NULL
		|| map->west_text == NULL
		|| map->east_text == NULL
		|| map->rgb_control != 2)
		return (1);
	return (0);
}

int	textures(char *path, t_map *map)
{
	int		fd;
	int		i;
	char	*tmp;
	char	*tmp_2;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	tmp = get_next_line(fd);
	if (!tmp)
		return (1);
	while (tmp)
	{
		i++;
		if (check_if_them_full(map) == 0 && tmp[0] != '\n')
		{
			map->map_p = ft_strdup(tmp);
			free (tmp);
			tmp = get_next_line(fd);
			if (!tmp)
				return (1);
			while (tmp && tmp[0] != '\n')
			{
				tmp_2 = ft_strjoin(map->map_p, tmp);
				map->map_p = ft_strdup(tmp_2);
				free(tmp_2);
				free (tmp);
				tmp = get_next_line (fd);
			}
		//	if (tmp)  // altta ayrı harita için
		//		return(1);
			return (i);
		}
		if (tmp[0] != '\n' && take_texts(tmp, map, 0, 1))
		{
			free (tmp);
			return (1);
		}
		free (tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	if (check_if_them_full(map))
		return (1);
	return (i);
}

int	check_texts_rgb(t_map *map, char *av1)
{
	int		map_starter;
	
	if (check_map_name(av1) == 1)
	{
		printf("Wrong filename!\n");
		return (1);
	}
	ft_init(map);
	map_starter = textures(av1, map);
	if (map_starter == 1)
	{
		printf("Map includes wrong, missing or extra characters!\n");
		return (1);
	}
	else if (map_starter > 6)
		return (0);
	else // map_starter 2 3 4 veya > 6
	{
		return (1);
	}
	return (0);
}
