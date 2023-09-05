/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:53 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/05 21:19:41 by havyilma         ###   ########.fr       */
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
	if (create_map_dp(set.map) || valid_char((set.map)->map_p) || valid_map(set.map))
		return (ft_free_str(&set));
	start_mlx(&set);
	// ray casting

	ft_mlx(set);
	return (0);
}
