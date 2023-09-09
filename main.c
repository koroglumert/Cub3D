/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:53 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/09 17:08:44 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int main(int ac, char **av)
{
	t_setting set;
	
	if (ac != 2)
	{
		printf("Wrong argument count!\n");
		return (1);
	}
	ft_init(&set);
	if (check_texts_rgb(set.map, av[1]))
		return (ft_free_str(&set));
	if (create_map_dp(set.map) || valid_char((set.map)->map_p) || valid_map(set.map) || where_am_i(&set, set.map->map))
		return (ft_free_str(&set));
	set.map->win_i = 1920;
	set.map->win_j = 1080;
	start_mlx(&set);
//	ray casting


	return (0);
}
