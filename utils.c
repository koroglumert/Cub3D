/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:18:48 by havyilma          #+#    #+#             */
/*   Updated: 2023/10/07 18:00:09 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_setting *set)
{
	set->map = malloc(sizeof(t_map));
	set->mlx = malloc(sizeof(t_mlx));
	set->rc = malloc(sizeof(t_rc));
	set->map->map_p = NULL;
	set->map->north_text = NULL;
	set->map->south_text = NULL;
	set->map->west_text = NULL;
	set->map->east_text = NULL;
	set->map->rgb_c = malloc(sizeof(int) * 3);
	set->map->rgb_c[0] = -1;
	set->map->rgb_c[1] = -1;
	set->map->rgb_c[2] = -1;
	set->map->rgb_f = malloc(sizeof(int) * 3);
	set->map->rgb_f[0] = -1;
	set->map->rgb_f[1] = -1;
	set->map->rgb_f[2] = -1;
	set->press_w = 0;
	set->press_a = 0;
	set->press_s = 0;
	set->press_d = 0;
	set->direct_right = 0;
	set->direct_left = 0;
	set->move_speed = 0.05;
	set->rot_speed = 0.03;
	set->map->rgb_control = 0;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	a = malloc(sizeof(char) * (len + 1));
	if (!a)
		return (NULL);
	while (s[start] && len != 0)
	{
		a[i] = s[start];
		i++;
		start++;
		len--;
	}
	a[i] = '\0';
	return (a);
}

int	ft_atoi(const char *str)
{
	long		i;
	long		sign;
	long		result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = (result * 10) + str[i] - 48;
		i++;
		if (result * sign > 2147483647)
			return (-1);
		if (result * sign < -2147483648)
			return (0);
	}
	return (result * sign);
}

char	*ft_strdup(char *s1)
{
	char	*temp;
	int		length;
	int		i;

	i = 0;
	length = ft_strlen(s1);
	temp = malloc(sizeof(char) * (length + 1));
	if (!temp)
		return (NULL);
	while (s1 && s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

int	print_error(char *str, int t)
{
	if (t > 2)
		close (t);
	printf("Error\n%s\n", str);
	return (1);
}
