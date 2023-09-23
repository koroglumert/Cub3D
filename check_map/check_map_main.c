/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:21 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/23 16:24:58 by havyilma         ###   ########.fr       */
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
	while (str[*i] == ' ' || str[*i] == '\n' || str[*i] == '\t')
		*i += 1;
	if (str[*i])
		return(1);
	return (0);	
}

void	fill_sing_pnt(char *add, t_map *map)
{
	char *tmp;

	if (map->map_p == NULL)
		map->map_p = ft_strdup(add);
	else
	{
		tmp = ft_strdup(map->map_p);
		free (map->map_p);
		map->map_p = ft_strjoin(tmp, add);
	}
}

void	ft_check_next(int fd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return ;
		if (while_for_space (tmp, &i) == 1)
			exit (print_error());
		if (tmp)
			free (tmp);
	}
}


int ft_take_map(t_map *map, int fd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_next_line(fd);
	if (!tmp)
		return (1);
	while (tmp)
	{
		if (while_for_space (tmp, &i) == 1)
			fill_sing_pnt(tmp, map);
		else
			ft_check_next(fd);
		if (tmp)
			free (tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			return (1);
	}
	close(fd);
	return (0);
}

int	textures(char *path, t_map *map)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	while(check_if_them_full(map) == 1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return (1);
		if (while_for_space (tmp, &i) == 1)
			take_texts(tmp, map, i, 0);
		free(tmp);
	}
	if (check_if_them_full(map) == 0)
		return (ft_take_map(map, fd));
	return (1);
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

	if (check_map_name(av1) == 1)
	{
		printf("Error\nWrong filename!\n");
		return (1);
	}
	textures(av1, map);
	return (0);
}
