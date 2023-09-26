/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:21:52 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/26 12:04:00 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fill_them(char *str, int *i, int type, t_map *map)
{
	int	finish;

	*i += 2;
	while (str[*i] == 32)
		(*i)++;
	finish = *i;
	while (str[finish] != '\0' && str[finish] != '\n' && str[finish] > 32)
		finish++;
	if (type == 'S')
		map->south_text = ft_substr(str, *i, finish - *i);
	else if (type == 'N')
		map->north_text = ft_substr(str, *i, finish - *i);
	else if (type == 'W')
		map->west_text = ft_substr(str, *i, finish - *i);
	else if (type == 'E')
		map->east_text = ft_substr(str, *i, finish - *i);
	while (str[finish] == 32)
		finish++;
	*i = finish;
	if (str[finish] != '\n' && str[finish] != '\0')
		return (1);
	return (0);
}

int	fill_c(t_map *map, int *i, int rgb, char *str)
{
	char	*number;
	int		finish;

	while (str[*i] == 32)
		(*i)++;
	finish = *i;
	while (str[finish] >= 48 && str[finish] <= 57)
		finish++;
	if (*i == finish && rgb == 0)
		return (1);
	number = ft_substr(str, *i, finish - *i);
	map->rgb_c[rgb] = ft_atoi(number);
	free (number);
	*i = finish;
	if (rgb == 2)
		map->rgb_control += 1;
	return (0);
}

int	fill_f(t_map *map, int *i, int rgb, char *str)
{
	char	*number;
	int		finish;

	while (str[*i] == 32)
		(*i)++;
	finish = *i;
	while (str[finish] >= 48 && str[finish] <= 57)
		finish++;
	if (*i == finish && rgb == 0)
		return (1);
	number = ft_substr(str, *i, finish - *i);
	map->rgb_f[rgb] = ft_atoi(number);
	free (number);
	*i = finish;
	if (rgb == 2)
		map->rgb_control += 1;
	return (0);
}

int	fill_intpointr(char *str, int *i, int type, t_map *map)
{
	int		rgb;

	rgb = 0;
	*i += 1;
	while (str[*i] == 32)
		(*i)++;
	while (str[*i] && rgb < 3)
	{
		while (str[*i] == 32)
			(*i)++;
		if (type == 'C')
			fill_c(map, i, rgb, str);
		else if (type == 'F')
			fill_f(map, i, rgb, str);
		if (rgb != 2 && str[*i] == ',')
			(*i)++;
		rgb += 1;
	}
	while (str[*i] == 32)
		(*i)++;
	if (rgb != 3 || (str[*i] != '\0' && str[*i] != '\n'))
		return (1);
	return (0);
}

int	take_texts(char *str, t_map *map, int i, int flg)
{
	if (str[i] && str[i + 1] && str[i] == 'N' && str[i + 1] == 'O')
		flg = fill_them(str, &i, 'N', map);
	else if (str[i] && str[i + 1] && str[i] == 'S' && str[i + 1] == 'O')
		flg = fill_them(str, &i, 'S', map);
	else if (str[i] && str[i + 1] && str[i] == 'W'
		&& str[i + 1] == 'E')
		flg = fill_them(str, &i, 'W', map);
	else if (str[i] && str[i + 1] && str[i] == 'E'
		&& str[i + 1] == 'A')
		flg = fill_them(str, &i, 'E', map);
	else if (str[i] && str[i] == 'F')
		flg = fill_intpointr(str, &i, 'F', map);
	else if (str[i] && str[i] == 'C')
		flg = fill_intpointr(str, &i, 'C', map);
	else if (str[i] == '\n')
		return (0);
	else
		exit (print_error("Elements are wrong", 0));
	if (flg == 1)
		exit (print_error("Map includes wrong, missing or extra characters!",
				0));
	return (0);
}
