/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:35:42 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/29 19:35:43 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("[%s]\n", map[i]);
		i++;
	}
}

int	check_map(t_map *map, char *map_name)
{
	int		map_len;
	int		i;
	int		fd;
	char	**map_contant;

	i = 0;
	map_contant = NULL;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (error1(), 1);
	map_len = get_lines(fd);
	map_contant = readfilecontant(map_name, 0, map_len, -1);
	if (!map_contant)
		return (1);
	if (check_texture_and_colors(map, map_contant, &i))
		return (error43(), 1);
	if (check_map_contant(map, map_contant, i))
		return (error2(), 1);
	return (0);
}
