/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilitis4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:43:07 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/29 19:43:08 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	basic_init(t_mapheader *mapheader)
{
	mapheader->no = 0;
	mapheader->we = 0;
	mapheader->ea = 0;
	mapheader->so = 0;
	mapheader->f = 0;
	mapheader->c = 0;
}

int	valid_colors(t_map *map, char *str, int f_or_c)
{
	char	**tmp;
	int		i;

	tmp = NULL;
	i = 0;
	tmp = ft_split(str, ',');
	if (!tmp)
		return (1);
	while (i < 3 && tmp[i] && tmp[i][0])
	{
		if (ft_atoi(tmp[i]) > 255 || ft_atoi(tmp[i]) < 0 || !ft_isnum(tmp[i]))
			return (1);
		if (f_or_c)
			map->ceiling[i] = ft_atoi(tmp[i]);
		else
			map->floor[i] = ft_atoi(tmp[i]);
		i++;
	}
	if (i != 3)
		return (1);
	if (tmp[i])
		return (1);
	return (0);
}
