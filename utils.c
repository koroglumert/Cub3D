/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:18:48 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/05 19:42:57 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_setting *set)
{
	set->map = malloc(sizeof(t_map));
	set->mlx = malloc(sizeof(t_mlx));
	set->map->north_text = NULL;
	set->map->south_text = NULL;
	set->map->west_text = NULL;
	set->map->east_text = NULL;
	set->map->map_p = NULL;
	set->map->rgb_c = malloc(sizeof(int) * 3);
	set->map->rgb_f = malloc(sizeof(int) * 3);
}

int	ft_free_str(t_setting *set)
{
	if (set->map->north_text)
		free (set->map->north_text);
	if (set->map->south_text)
		free (set->map->south_text);
	if (set->map->west_text)
		free (set->map->west_text);
	if (set->map->east_text)
		free (set->map->east_text);
	if (set->map->map_p)
		free (set->map->map_p);	
	if (set->map->rgb_c)
		free (set->map->rgb_c);
	if (set->map->rgb_f)
		free (set->map->rgb_f);
	if (set->map)
		free (set->map);
//	set->mlx
	return (1);
}
