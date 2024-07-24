/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfilecontant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:42:45 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/29 19:42:46 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_lines(int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
	}
	close(fd);
	return (i);
}

char	**readfilecontant(char *mapname, int fd, int len, int i)
{
	char	*line;
	char	**map;

	line = NULL;
	map = (char **)malloc(sizeof(char *) * (len + 1));
	if (!map)
		return (NULL);
	fd = open(mapname, O_RDONLY);
	while (++i < len)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
		{
			map[i] = ft_substr(line, 0, (ft_strlen(line) - 1));
			free(line);
		}
		else
			map[i] = line;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}
