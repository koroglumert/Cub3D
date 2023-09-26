/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:04:10 by mkoroglu          #+#    #+#             */
/*   Updated: 2023/09/26 11:58:18 by havyilma         ###   ########.fr       */
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

int	while_for_space(char *str, int *i)
{
	*i = 0;
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		*i += 1;
	if (str[*i])
		return (1);
	return (0);
}

void	fill_sing_pnt(char *add, t_map *map)
{
	if (map->map_p == NULL)
		map->map_p = ft_strdup(add);
	else
		map->map_p = ft_strjoin(map->map_p, add);
}

void	ft_dp_2(t_map *map, int length)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (i < length)
	{
		start = j;
		while (map->map_p[j] != '\n' && map->map_p[j] != '\0')
			j++;
		map->map[i] = ft_substr(map->map_p, start, j - start);
		if (map->map_p[j] == '\n')
			j++;
		i++;
	}
}
