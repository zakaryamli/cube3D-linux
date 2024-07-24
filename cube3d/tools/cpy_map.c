/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:42:01 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/29 19:42:02 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**create_cpy(char **map)
{
	char	**cpymap;
	int		i;
	int		x;

	x = 0;
	i = -1;
	while (map[x])
		x++;
	cpymap = (char **)malloc(sizeof(char *) * (x + 1));
	if (!cpymap)
		return (NULL);
	while (map[++i])
	{
		cpymap[i] = ft_strdup(map[i]);
	}
	cpymap[i] = NULL;
	return (cpymap);
}
