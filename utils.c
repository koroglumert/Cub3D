/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:18:48 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/30 13:49:02 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_map *map)
{
	map->north_text = NULL;
	map->south_text = NULL;
	map->west_text = NULL;
	map->east_text = NULL;
	map->map_p = NULL;
	map->rgb_c = malloc(sizeof(int) * 3);
	map->rgb_f = malloc(sizeof(int) * 3);
}

void	ft_free_str(t_map *map)
{
	if (map->north_text)
		free (map->north_text);
	if (map->south_text)
		free (map->south_text);
	if (map->west_text)
		free (map->west_text);
	if (map->east_text)
		free (map->east_text);
	if (map->rgb_c)
		free(map->rgb_c);
	if (map->rgb_f)
		free(map->rgb_f);
}
