/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utilities.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:44:15 by zyamli            #+#    #+#             */
/*   Updated: 2024/07/23 18:50:04 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	rotation_z()
// {
// 	double	a;
// 	double	b;

// 	a = *(data->a);
// 	b = *(data->b);
// 	data->a->x = cos(data->gama) * a.x - sin(data->gama) * a.y;
// 	data->a->y = sin(data->gama) * a.x + cos(data->gama) * a.y;
// 	data->b->x = cos(data->gama) * b.x - sin(data->gama) * b.y;
// 	data->b->y = sin(data->gama) * b.x + cos(data->gama) * b.y;
// }

int	close_window(t_map *info)
{
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((red << 16) | (green << 8) | blue);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT) {

		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

// int blend_pixel(int color1, int color2, double p)
// {
// 		int a;
// 		int r;
// 		int g;
// 		int b;

// 		a = (int)((1 - p) * ((color1 >> 24) & 0xFF) + p * ((color2 >> 24) & 0xFF));
// 		r = (int)((1 - p) * ((color1 >> 16) & 0xFF) + p * ((color2 >> 16) & 0xFF));
// 		g = (int)((1 - p) * ((color1 >> 8) & 0xFF) + p * ((color2 >> 8) & 0xFF));
// 		b = (int)((1 - p) * (color1 & 0xFF) + p * (color2 & 0xFF));
// 		return (encode_rgb(r, g, b));
// }



int is_wall(t_map *map, double x, double y)
{
	int i;
	int j;

	// Convert floating-point coordinates to map indices
	i =  (int)((y / TILE_SIZE));
	j = (int)((x / TILE_SIZE));
	// printf("%d %d map %c\n", i, j, map->map[i][j]);
	// Check if the indices are within the bounds of the map
	// if (i < 0 || i >= map->height || j < 0 || j >= map->width)
	//     return 1; // Out of bounds is considered a wall

	// Check the map array for a wall
	return (map->map[i][j] == '1');
}



int key_hook(int keycode, t_map *map)
{
	double temp_x = map->position_x;
	double temp_y = map->position_y;
	double move_speed = 4;// Adjust speed as needed
	// printf("keycode %d\n", keycode);

	if (keycode == 53)
	{
		mlx_destroy_window(map->mlx, map->win);
		exit(0);
	}
	else if (keycode == 13 || keycode == 126) // Forward
	{
		temp_x = map->position_x + cos(map->rotation_angle) * move_speed;
		temp_y = map->position_y + sin(map->rotation_angle) * move_speed;
	}
	else if (keycode == 1 || keycode == 125) // Backward
	{
		temp_x = map->position_x - cos(map->rotation_angle) * move_speed;
		temp_y = map->position_y - sin(map->rotation_angle) * move_speed;
	}
	else if (keycode == 124) // Rotate right
		map->rotation_angle += ((M_PI / 180) * 4);
	else if (keycode == 123) // Rotate left
		map->rotation_angle -= ((M_PI / 180) * 4);
	else if (keycode == 0) // Strafe left
	{
		temp_x = map->position_x + sin(map->rotation_angle) * move_speed;
		temp_y = map->position_y - cos(map->rotation_angle) * move_speed;
	}
	else if (keycode == 2) // Strafe right
	{
		temp_x = map->position_x - sin(map->rotation_angle) * move_speed;
		temp_y = map->position_y + cos(map->rotation_angle) * move_speed;
	}

	// Ensure the angle is within 0 to 2 * PI
	if (map->rotation_angle < 0)
		map->rotation_angle += 2 * M_PI;
	if (map->rotation_angle >= 2 * M_PI)
		map->rotation_angle -= 2 * M_PI;

	// Perform collision checks
	bool can_move_x = (is_wall(map, temp_x, map->position_y) == 0);
	bool can_move_y = (is_wall(map, map->position_x, temp_y) == 0);

	// Update position based on collisions
	if (can_move_x && can_move_y) // Can move both x and y
	{
		map->position_x = temp_x;
		map->position_y = temp_y;
	}
	else if (can_move_x) // Can move x only
	{
		map->position_x = temp_x;
	}
	else if (can_move_y) // Can move y only
	{
		map->position_y = temp_y;
	}

	ft_render_the_game(map);
	return (0);
}




