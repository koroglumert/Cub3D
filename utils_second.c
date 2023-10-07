/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:56:14 by havyilma          #+#    #+#             */
/*   Updated: 2023/10/07 18:05:01 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

char	**ft_copy_double_array(char **str)
{
	char	**new;
	int	i;
	int	j;

	i = 0;
	while (str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	new[i] = 0;
	i = 0;
	while (str[i])
	{
		j = ft_strlen(str[i]);
		new[i] = malloc(sizeof(char) * (j + 1));
		new[i][j] = 0;
		j = 0;
		while (str[i][j])
		{
			new[i][j] = str[i][j];
			j++;
		}
		i++;
	}
	return (new);
}
