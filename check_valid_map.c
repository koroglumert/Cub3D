/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:24:37 by havyilma          #+#    #+#             */
/*   Updated: 2023/08/30 14:07:55 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_char(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while(str[i])
	{
		printf("+++ %c\n", str[i]);
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'E' || str[i] == 'S')
			flag += 1;
		if (!(str[i] == '0' || str[i] == '1' || str[i] == ' '
			|| str[i] == 'N' || str[i] == 'W' 
			|| str[i] == 'E' || str[i] == 'S' || str[i] == '\n'))
		{
			printf ("Wrong input!\n");
			return (1);
		}
		if (flag != 1)
		{
			printf ("Too many places to born!\n");
			return (1);
		}
		i++;
		
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
	map->map[i] = NULL;
	return(0);
}
/*
int	is_map_valid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->length)
	{
		if (map->map[0][j] != '1')
		{
			printf("Map is not covered by walls!\n");
			return (1);
		}
	}	
		
}
*/
