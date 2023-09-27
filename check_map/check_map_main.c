/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:21 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/27 18:36:50 by havyilma         ###   ########.fr       */
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
		{
			if (tmp)
				free (tmp);
			exit (print_error("wrong map", 0));
		}
		if (tmp)
			free (tmp);
	}
}

int	ft_take_map(t_map *map, int fd, int i)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (while_for_space (tmp, &i) == 0)
	{
		if (tmp)
			free(tmp);
		tmp = get_next_line(fd);
	}
	if (!tmp)
		return (print_error("wrong map", fd));
	while (tmp)
	{
		if (while_for_space (tmp, &i) == 1)
			fill_sing_pnt(tmp, map);
		else
			ft_check_next(fd);
		if (tmp)
			free (tmp);
		tmp = get_next_line(fd);
	}
	if (tmp)
		free(tmp);
	close (fd);
	return (0);
}

int	textures(char *path, t_map *map)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(print_error("Wrong file", fd));
	tmp = get_next_line(fd);
	if (!tmp)
		exit(print_error("NULL File", fd));
	while (tmp && check_if_them_full(map) == 1)
	{
		if (while_for_space (tmp, &i) == 1)
			take_texts(tmp, map, i, 0);
		if (tmp)
			free(tmp);
		if (check_if_them_full(map) == 1)
			tmp = get_next_line(fd);
	}
	if (check_if_them_full(map) == 0)
		return (ft_take_map(map, fd, i));
	return (1);
}

int	check_map_name(char *av1)
{
	int	i;
	int	len;

	i = ft_strlen(av1);
	len = i;
	if (i <= 4)
		return (1);
	while (len <= i && av1[len] != '.')
		len--;
	if (i - len < 4 && ((av1[len - 1] >= 65
				&& av1[len - 1] <= 90) || (av1[len - 1] >= 97
				&& av1[len - 1] <= 122)))
		return (1);
	i = len;
	if (!(av1[i] == '.' && av1[i + 1] == 'c'
			&& av1[i + 2] == 'u' && av1[i + 3] == 'b') || av1[i - 1] == '/')
		return (1);
	return (0);
}

int	check_texts_rgb(t_map *map, char *av1)
{
	if (check_map_name(av1) == 1)
		exit(print_error("Wrong filename!", 0));
	if (textures(av1, map))
		exit(print_error("Wrong map!", 0));
	return (0);
}
