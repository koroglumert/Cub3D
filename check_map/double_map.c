/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:56:52 by havyilma          #+#    #+#             */
/*   Updated: 2023/10/07 19:59:38 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_is_character(char c)
{
	if (c == '1' || c == '0' || c == 'W' || c == 'N' || c == 'E' || c == 'S')
		return (1);
	return (0);
}

void	ft_control_double_map(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_is_character(str[i][j]))
			{
				printf("\nERROR '%c'\n", str[i][j]);
				ft_free_double_array(str);
				exit(print_error("Error! Double Map.\n", 1));
			}
			j++;
		}
		i++;
	}
}

void	ft_recursive_double_map(char **str, int i, int j)
{
	if (!str[i] || j >= ft_strlen(str[i]) || !ft_is_character(str[i][j]))
		return ;
	str[i][j] = 'X';
	if (i >= 1)
	{
		ft_recursive_double_map(str, i - 1, j);
		ft_recursive_double_map(str, i - 1, j + 1);
	}
	if (j >= 1)
	{
		ft_recursive_double_map(str, i, j - 1);
		ft_recursive_double_map(str, i + 1, j - 1);
	}
	if (i >= 1 && j >= 1)
		ft_recursive_double_map(str, i - 1, j - 1);
	ft_recursive_double_map(str, i + 1, j);
	ft_recursive_double_map(str, i, j + 1);
	ft_recursive_double_map(str, i + 1, j + 1);
}

void	ft_check_double_map(char **str)
{
	int	j;

	j = 0;
	str = ft_copy_double_array(str);
	while (str[0][j])
	{
		if (ft_is_character(str[0][j]))
			break ;
		j++;
	}
	ft_recursive_double_map(str, 0, j);
	ft_control_double_map(str);
	ft_free_double_array(str);
}
