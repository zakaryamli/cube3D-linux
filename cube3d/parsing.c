/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:43:46 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/29 19:43:47 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_important_values(t_map *info, int i, int j)
{
	char	x;

	x = 'A';
	info->height = 1500;
	info->width = 1000;
	while (info->map[i])
	{
		while (info->map[i][j])
		{
			x = info->map[i][j];
			if (x == 'N' || x == 'S' || x == 'E' || x == 'W')
			{
				info->player_x = (j + 0.5) * 32;
				info->player_y = (i + 0.5) * 32;
				info->direction = x;
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int	parsing(t_map *map, char *map_name)
{
	if (check_name(map_name))
		return (error5(), 1);
	if (check_map(map, map_name))
		return (1);
	set_important_values(map, 0, 0);
	return (0);
}
