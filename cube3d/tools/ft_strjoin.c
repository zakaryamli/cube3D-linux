/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:36:40 by zyamli            #+#    #+#             */
/*   Updated: 2024/06/29 19:36:41 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		s2_len;
	int		i;
	int		j;

	s2_len = ft_strlen(s2);
	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) + s2_len + 1) * sizeof(char));
	if (!str)
		return (free(s1), s1 = NULL, NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	s1 = NULL;
	return (str);
}
