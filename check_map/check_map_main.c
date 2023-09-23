/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:21 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/23 20:25:53 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			exit (print_error("Elements are wrong"));
		if (tmp)
			free (tmp);
	}
}

int	ft_take_map(t_map *map, int fd, int i)
{
	char	*tmp;

	tmp = get_next_line(fd);
	if (!tmp)
		return (1);
	while (while_for_space (tmp, &i) == 0)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
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
		exit(print_error("Wrong file"));
	tmp = get_next_line(fd);
	if (!tmp)
		exit(print_error("NUll File"));
	while (check_if_them_full(map) == 1)
	{
		if (while_for_space (tmp, &i) == 1)
			take_texts(tmp, map, i, 0);
		free(tmp);
		tmp = get_next_line(fd);
		if (!tmp)
			return (1);
	}
	if (check_if_them_full(map) == 0)
		return (ft_take_map(map, fd, i));
	return (1);
}

int	check_map_name(char *av1)
{
	int	i;

	i = ft_strlen(av1);
	if (i <= 4)
		return (1);
	i--;
	if (!(av1[i] == 'b' && av1[i - 1] == 'u'
			&& av1[i - 2] == 'c' && av1[i - 3] == '.'))
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
