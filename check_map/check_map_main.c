/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:21 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/19 19:56:40 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_rgb_valid(int *c, int *f)
{
	int	i;

	i = 0;
	while (i <= 2)
	{
		if (!((c[i] >= 0 && c[i] <= 255) && (f[i] >= 0 && f[i] <= 255)))
			return (1);
		i++;
	}
	return (0);
}

int	check_if_them_full(t_map *map)
{
	if (map->north_text == NULL 
		|| map->south_text == NULL
		|| map->west_text == NULL
		|| map->east_text == NULL
		|| map->rgb_control != 2 || is_rgb_valid(map->rgb_c, map->rgb_f))
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
			close (fd);
			return (i);
		}
		if (tmp[0] != '\n' && take_texts(tmp, map, 0 ,0))
		{
			free(tmp);
			close (fd);
			return (1);
		}
		free (tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	return (i);
}

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

int	check_texts_rgb(t_map *map, char *av1)
{
	int		map_starter;
	
	if (check_map_name(av1) == 1)
	{
		printf("Wrong filename!\n");
		return (1);
	}
	map_starter = textures(av1, map);
	if (map_starter == 1)
	{
		printf("Map includes wrong, missing or extra characters!\n");
		return (1);
	}
//	else // map_starter 2 3 4 veya > 6

	return (0);
}
