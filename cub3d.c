/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkoroglu <mkoroglu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:49:53 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/20 03:16:02 by mkoroglu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_take_directs(t_setting *set)
{
	set->player->dir_x = 0.0; //MERT: BU iki satır neden var? silinince normda çözülür.
	set->player->dir_y = 0.0; 
	if (set->map->map[set->player->ply_i][set->player->ply_j] == 'N')
	{
		set->player->dir_x = 1.0; 
		set->player->plane_y = 0.66;
	}
	else if (set->map->map[set->player->ply_i][set->player->ply_j] == 'S')
	{
		set->player->dir_x = -1.0; 		
		set->player->plane_y = -0.66;
	}
	else if (set->map->map[set->player->ply_i][set->player->ply_j] == 'E')
	{
		set->player->plane_x = 0.66;
		set->player->dir_y = 1.0;
	}
	else if (set->map->map[set->player->ply_i][set->player->ply_j] == 'W')
	{
		set->player->plane_x = -0.66;
		set->player->dir_y = -1.0;
	}
	set->player->x = (double)(set->player->ply_j) + 0.5; //MERT: Bu neden var?
	set->player->y = (double)(set->player->ply_i) + 0.5;
	return(0);
}

static void	ft_take_rgb_f_c(t_setting *set)
{
	set->map->rgb_ceiling = (set->map->rgb_c[0] << 16) 
		+ (set->map->rgb_c[1] << 8) + set->map->rgb_c[2];
	set->map->rgb_floor = (set->map->rgb_f[0] << 16) 
		+ (set->map->rgb_f[1] << 8) + set->map->rgb_f[2];
}

int main(int ac, char **av)
{
	t_setting set;
	
	if (ac != 2)
	{
		printf("Wrong argument count!\n");
		return (1);
	}
	//set = malloc(sizeof(t_setting)); //MERT: leak bırakmaz içerideki hiçbir malloc çünkü mainde tutuyır adresi (silince bırakır mı emin değilim)
	ft_init(&set);

	//MERT: Buradan başlayıp
	if (check_texts_rgb(set.map, av[1]) || create_map_dp(set.map) 
		|| valid_char((set.map)->map_p)
		|| valid_map(set.map) || where_am_i(&set, set.map->map))
		return (0); //leak olmayacağı için free'ye de gerek yok.
	set.map->img_h = 64;
	set.map->img_w = 64;
	ft_check_xpm(set.map);
	ft_take_directs(&set);
	ft_take_rgb_f_c(&set);
	//MERT: Bu kısma kadar yeni bir dosya veya check main fonksiyonu ile yönetilmeli.
	mlx_start(&set);
	return (0);
}
