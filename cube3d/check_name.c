/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:45:00 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/29 19:45:01 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_it(char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 3;
	while (str[i])
		i++;
	if (i > 0)
		i--;
	else
		return (1);
	while (str[i] && i >= size && size > 0)
	{
		i--;
		size--;
	}
	if (ft_strcmp(&str[i], ".cub") != 0)
		return (1);
	return (0);
}

int	check_name(char *str)
{
	return (check_it(str));
}
