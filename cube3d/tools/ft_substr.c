/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:36:13 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/29 19:36:14 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	char	*ft_cpystr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*str;

	i = 0;
	size = ft_strlen(s);
	if (len > size - start)
	{
		len = size - start;
		str = (char *)malloc((size - start) * sizeof(char) + 1);
	}
	else
		str = (char *)malloc(len * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	// size_t	i;
	char	*str;

	// i = 0;
	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) <= start)
	{
		str = (char *)malloc(1);
		if (str == NULL)
			return (NULL);
		*str = '\0';
		return (str);
	}
	str = ft_cpystr(s, start, len);
	return (str);
}
