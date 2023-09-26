/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: havyilma <havyilma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:38:40 by havyilma          #+#    #+#             */
/*   Updated: 2023/09/26 02:29:28 by havyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

int	ft_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*(s + i))
	{
		if (*(s + i) == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		new[i++] = s1[j++];
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	free (s1);
	return (new);
}

char	*ft_get_line(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!*str)
		return (NULL);
	while (str[j] != '\n' && str[j])
		j++;
	new = malloc(sizeof(char) * (j + 2));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[j] != '\n' && str[j])
		new[i++] = str[j++];
	if (str[j] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

char	*ft_rest_str(char *old)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	if (!old)
		return (NULL);
	while (old[j] && old[j] != '\n')
		j++;
	if (!*(old + j))
	{
		free(old);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_strlen(old) - j + 1));
	if (!new)
		return (NULL);
	i = 0;
	j++;
	while (old[j])
		new[i++] = old[j++];
	new[i] = '\0';
	free(old);
	return (new);
}
