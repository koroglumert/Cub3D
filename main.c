/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:53 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/01 15:55:06 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int main(int ac, char **av)
{
	t_map map;
	
	if (ac != 2)
	{
		printf("Wrong argument count!\n");
		return (1);
	}
	if (check_texts_rgb(&map, av[1]))
	{
		ft_free_str(&map);
		return(1);
	}
	if (create_map_dp(&map) || valid_char((&map)->map_p) || valid_map(&map))
	{
		//	ft_free_str(&map);
		return(1);
	}

	
	return (0);
}
