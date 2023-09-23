/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:24:37 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/23 16:27:51 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	where_am_i(t_setting *set, char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 'N' || str[i][j] == 'S'
				|| str[i][j] == 'W' || str[i][j] == 'E')
			{
				set->player->pos_y = (double)i;
				set->player->pos_x = (double)j;
				return (0);
			}
		}
	}
	return (0);
}

int	valid_char(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while(str[i])
	{
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'E' || str[i] == 'S')
			flag += 1;
		if (!(str[i] == '0' || str[i] == '1' || str[i] == ' '
			|| str[i] == 'N' || str[i] == 'W' 
			|| str[i] == 'E' || str[i] == 'S' || str[i] == '\n'))
		{
			printf ("Error\nWrong input!\n");
			return (1);
		}
		i++;
		
	}
	if (flag != 1)
	{
		printf ("Error\nToo many places to born!\n");
		return (1);
	}
	return (0);
}

int	create_map_dp(t_map *map)
{
	int		i;
	int		length;
	int		j;
	int		start;

	i = -1;
	length = 0;
	while(map->map_p[++i])
		if(map->map_p[i] == '\n' || map->map_p[i] == '\0')
			length++;
	map->map_length = length;
	map->map = malloc(sizeof(char *) * (length + 1));
	map->map[length] = NULL;
	i = -1;
	j = 0;
	while (++i < length)
	{
		start = j;
		while (map->map_p[j] != '\n' && map->map_p[j] != '\0')
			j++;
		map->map[i] = ft_substr(map->map_p, start, j - start);
		if(map->map_p[j] == '\n')
			j++;
	}
	return(0);
}

int	check_zero(char **map, int i, int j, t_map *m)
{
	if(i == 0 || j == 0 || (i + 1 == m->map_length) || (j + 1 == ft_strlen(map[i])))
		return (1);
	if (j + 1 > ft_strlen(map[i - 1]))
		return (1);
	if (map[i + 1] && (j + 1 > ft_strlen(map[i + 1])))
		return (1);
	if (map[i + 1][j] == 32 || map[i - 1][j] == 32 
		|| map[i][j - 1] == 32 || map[i][j + 1] == 32)
		return (1);
	return (0);
}

int	valid_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->map_length)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 48)
			{
				if (check_zero(map->map, i, j, map))
				{
					printf("Error\nWrong map!\n");
					return(1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);	
}

