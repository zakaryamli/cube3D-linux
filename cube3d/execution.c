/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli00@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:35:32 by zyamli            #+#    #+#             */
/*   Updated: 2024/07/11 10:43:44by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void put_circle(t_map *map, int xc, int yc, int r, int color) {
//     int x = r;
//     int y = 0;
//     int err = 0;

//     while (x >= y) {
//         my_mlx_pixel_put(&map->img, xc + x, yc + y, color);
//         my_mlx_pixel_put(&map->img, xc + y, yc + x, color);
//         my_mlx_pixel_put(&map->img, xc - y, yc + x, color);
//         my_mlx_pixel_put(&map->img, xc - x, yc + y, color);
//         my_mlx_pixel_put(&map->img, xc - x, yc - y, color);
//         my_mlx_pixel_put(&map->img, xc - y, yc - x, color);
//         my_mlx_pixel_put(&map->img, xc + y, yc - x, color);
//         my_mlx_pixel_put(&map->img, xc + x, yc - y, color);

//         if (err <= 0) {
//             y += 1;
//             err += 2 * y + 1;
//         }
//         if (err > 0) {
//             x -= 1;
//             err -= 2 * x + 1;
//         }
//     }
// }


static void find_player(t_map *map) {
	int i = 0;
	int j = 0;
	while (map->map[i]) {
		j = 0;
		while (map->map[i][j]) {
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W' || map->map[i][j] == 'E') {
				map->position_x = j * TILE_SIZE + TILE_SIZE / 2;
				map->position_y = i * TILE_SIZE + TILE_SIZE / 2;
				if (map->map[i][j] == 'N')
					map->rotation_angle = 270 * (M_PI / 180);
				else if (map->map[i][j] == 'S')
					map->rotation_angle = 90 * (M_PI / 180);
				else if (map->map[i][j] == 'W')
					map->rotation_angle = 180 * (M_PI / 180);
				else if (map->map[i][j] == 'E')
					map->rotation_angle = 0;
				return;
			}
			j++;
		}
		i++;
	}
}



void draw_line(t_map *map, int x0, int y0, int x1, int y1, int color) {
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;
	int e2;

	while (1) {
		my_mlx_pixel_put(&map->img, x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		e2 = err * 2;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

static double normalize_angle(double angle)
{
	double	res;

	res = fmod(angle, 2 * M_PI);
	if (res < 0){
		res += 2 * M_PI;
	}
	return (res);
}


static double distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

static int has_wall_at(t_map *map, double x, double y)
{
	int map_index_x = 0;
	int map_index_y = 0;

	map_index_x = (int)((x) / TILE_SIZE);
	map_index_y = (int)((y) / TILE_SIZE);
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) // Changed > to >=
		return (1);
	if (map_index_x >= map->width || map_index_y >= map->height)
		return (1);
	return ((map->map[map_index_y][map_index_x] == '1' || map->map[map_index_y][map_index_x] == ' '));
}
static  void ray_distance(t_map *map, t_ray *ray, int id)
{
	// Initialize horizontal intersection values
	ray->horiz_wall_hit = false;
	ray->h_wall_hit_x = 0;
	ray->h_wall_hit_y = 0;

	// Calculate horizontal intersections
	ray->intercect1_y = floor(map->position_y / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_down)
		ray->intercect1_y += TILE_SIZE;
	ray->intercect1_x = map->position_x + (ray->intercect1_y - map->position_y) / tan(ray->angle);

	ray->dy = TILE_SIZE;
	if (ray->ray_up)
		ray->dy *= -1;

	ray->dx = TILE_SIZE / tan(ray->angle);
	if (ray->ray_left && ray->dx > 0)
		ray->dx *= -1;
	if (ray->ray_right && ray->dx < 0)
		ray->dx *= -1;

	ray->next_horiz_touch_x = ray->intercect1_x;
	ray->next_horiz_touch_y = ray->intercect1_y;

	// Horizontal ray-casting
	while (ray->next_horiz_touch_x >= 0 && ray->next_horiz_touch_x <= map->width * TILE_SIZE &&
			ray->next_horiz_touch_y >= 0 && ray->next_horiz_touch_y <= map->height * TILE_SIZE)
	{
		if (has_wall_at(map, ray->next_horiz_touch_x, ray->next_horiz_touch_y - (ray->ray_up == 1)))
		{
			ray->horiz_wall_hit = true;
			ray->h_wall_hit_x = ray->next_horiz_touch_x;
			ray->h_wall_hit_y = ray->next_horiz_touch_y;
			break;
		}
		else
		{
			ray->next_horiz_touch_x += ray->dx;
			ray->next_horiz_touch_y += ray->dy;
		}
	}

	// Initialize vertical intersection values
	ray->vert_wall_hit = false;
	ray->v_wall_hit_x = 0;
	ray->v_wall_hit_y = 0;

	// Calculate vertical intersections
	ray->intercect1_x = floor(map->position_x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_right)
		ray->intercect1_x += TILE_SIZE;
	ray->intercect1_y = map->position_y + (ray->intercect1_x - map->position_x) * tan(ray->angle);

	ray->dx = TILE_SIZE;
	if (ray->ray_left)
		ray->dx *= -1;

	ray->dy = TILE_SIZE * tan(ray->angle);
	if (ray->ray_up && ray->dy > 0)
		ray->dy *= -1;
	if (ray->ray_down && ray->dy < 0)
		ray->dy *= -1;

	ray->next_vert_touch_x = ray->intercect1_x;
	ray->next_vert_touch_y = ray->intercect1_y;

	// Vertical ray-casting
	while (ray->next_vert_touch_x >= 0 && ray->next_vert_touch_x <= map->width * TILE_SIZE &&
		   ray->next_vert_touch_y >= 0 && ray->next_vert_touch_y <= map->height * TILE_SIZE)
	{
		if (has_wall_at(map, ray->next_vert_touch_x - (ray->ray_left == 1), ray->next_vert_touch_y))
		{
			ray->vert_wall_hit = true;
			ray->v_wall_hit_x = ray->next_vert_touch_x;
			ray->v_wall_hit_y = ray->next_vert_touch_y;
			break;
		}
		else
		{
			ray->next_vert_touch_x += ray->dx;
			ray->next_vert_touch_y += ray->dy;
		}
	}

	// Calculate distance to the nearest wall hit
	ray->distance = DBL_MAX;
	if (ray->horiz_wall_hit)
		ray->distance = distance_between_points(map->position_x, map->position_y, ray->h_wall_hit_x, ray->h_wall_hit_y);
	if (ray->vert_wall_hit)
	{
		double vert_distance = distance_between_points(map->position_x, map->position_y, ray->v_wall_hit_x, ray->v_wall_hit_y);
		if (vert_distance < ray->distance)
		{
			ray->distance = vert_distance;
			ray->horiz_wall_hit = false;
			ray->vert_wall_hit = true;
			ray->h_wall_hit_x = ray->v_wall_hit_x;
			ray->h_wall_hit_y = ray->v_wall_hit_y;
		}
	}

	map->distances[id] = ray->distance;
if (ray->horiz_wall_hit)
	{
		if (ray->ray_down)
			ray->south_face = true;
		else
			ray->north_face = true;
	}
	else if (ray->vert_wall_hit)
	{
		if (ray->ray_right)
			ray->east_face = true;
		else
			ray->west_face = true;
	}
	draw_line(map, map->position_x, map->position_y, ray->h_wall_hit_x, ray->h_wall_hit_y, 0x000090);
}

static void ray_facing(t_map *map, double ray_angle, int id)
{
	t_ray ray;

	ray.angle = normalize_angle(ray_angle);
	ray.intercect1_x = 0;
	ray.intercect1_y = 0;
	ray.dx = 0;
	ray.dy = 0;
	ray.ray_down  = (ray.angle > 0 && ray.angle < M_PI); // facing down
	ray.ray_up = !ray.ray_down;
	ray.ray_right = (ray.angle < 0.5 * M_PI || ray.angle > 1.5 * M_PI); // facing right
	ray.ray_left = !ray.ray_right;
	ray.north_face = false;
	ray.south_face = false;
	ray.east_face = false;
	ray.west_face = false;
	ray_distance(map, &ray, id);
	map->ray[id] = ray;
}


static void draw_rays(t_map *map, double *rays) {
	int i = 0;
	while (i < NUM_RAYS)
	{
		ray_facing(map, rays[i], i);
		printf(">>>ray id : %d { north %d south %d west %d east %d} \n",i, map->ray[i].north_face,
			map->ray[i].south_face, map->ray[i].west_face, map->ray[i].east_face);
		i++;
	}

}

static void rays_handler(t_map *map)
{
	// Ray casting
	map->distances = malloc(sizeof(double) * NUM_RAYS);
	if (!map->rays_ang)
		exit(1);
	map->rays_ang = malloc(sizeof(double) * NUM_RAYS);
	if (!map->rays_ang)
		exit(1);
	map->ray = malloc(sizeof(t_ray) * NUM_RAYS);
	if (!map->ray)
		exit(1);
	int i = 0;
	map->ray_angle = map->rotation_angle - (double)FOV / 2.f;
	while (i < NUM_RAYS) {
		map->rays_ang[i] = map->ray_angle;
		map->ray_angle += FOV / NUM_RAYS;
		i++;
	}

	draw_rays(map, map->rays_ang);
	// free(rays);
}




static void putplayer(t_map *map)
{
	int i = 0;
	int j = 0;
	int x_end = map->position_x + cos(map->rotation_angle) * 30;
	int y_end = map->position_y + sin(map->rotation_angle) * 30;

	// Draw the direction line
	while(i < NUM_RAYS)
	{
		draw_line(map, map->position_x, map->position_y, map->position_x + cos(map->rays_ang[i]) * 30, map->position_y + sin(map->rays_ang[i]) * 30, 0x9FF000);
		i++;

	}
	draw_line(map, map->position_x + 1, map->position_y + 1, x_end, y_end, 0xFF00FF);
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			my_mlx_pixel_put(&map->img, map->position_x + i, map->position_y + j, 0x00FF00);
			j++;
		}
		i++;
	}
	// Calculate the end point of the line based on the rotation angle
}

static void ceiling_floor(t_map *map)
{
	int x = 0;
	int y = 0;
	char *dst = map->img.addr;

	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			int pixel = (y * map->img.line_length) + (x * (map->img.bits_per_pixel / 8));
			*(unsigned int *)(dst + pixel) = encode_rgb(map->ceiling[0], map->ceiling[1], map->ceiling[2]);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			int pixel = (y * map->img.line_length) + (x * (map->img.bits_per_pixel / 8));
			*(unsigned int *)(dst + pixel) = encode_rgb(map->floor[0], map->floor[1], map->floor[2]);
			x++;
		}
		y++;
	}
	}

static void draw_block(t_map *map, int x, int y, int color) {
	int i = 0;
	int j = 0;
	while (i < TILE_SIZE - 1) {
		j = 0;
		while (j < TILE_SIZE - 1) {
			my_mlx_pixel_put(&map->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void draw_map(t_map *map)
{
	int i = 0;
	int j;
	// int x, y;
	int color;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			// Determine color based on map data
			if (map->map[i][j] == '1' || map->map[i][j] == ' ')
				color = 0x458D8C; // Wall and space color
			else
				color = 0xffc6ff; // Default color (open paths)
			draw_block(map, j * TILE_SIZE, i * TILE_SIZE, color);
			j++;
		}
		i++;
	}

	putplayer(map); // Assuming this function puts the player on the map
}


// static int get_pixel(t_data *texture, int x, int y)
// {
// 	char *dst;
// 	int color;

// 	dst = texture->addr + (y * texture->img_width + x * (texture->bits_per_pixel / 8));
// 	color = *(unsigned int *)dst;
// 	return color;
// }

static double	offset_x(t_ray *ray, t_data *texture)
{
	double	text_offset;
	double	wall_hit;

	if (ray->horiz_wall_hit == true)
	{
		wall_hit = ray->h_wall_hit_x * (texture->img_width / TILE_SIZE);
		text_offset = (int)wall_hit % texture->img_width;
	}
	else
	{
		wall_hit = ray->v_wall_hit_y * (texture->img_width / TILE_SIZE);
		text_offset = (int)wall_hit % texture->img_width;
	}
	return (text_offset);
}

static int wall_texture(t_map *map, int x, int y, int top, int height)
{
    t_ray *ray;
    t_data *texture = NULL;
	(void)top;
    // uint32_t *buff;
    double factor;
    double text_off_x;
    double text_off_y;
	int distance_from_top;

    // Ensure map and ray are valid
    if (!map || !map->ray) {
        printf("Error: Invalid map or ray.\n");
        return 0;
    }

    // Determine the texture to use based on the wall orientation
    ray = &map->ray[x];

    if (ray->north_face) {
        texture = &map->imges[0];
    } else if (ray->south_face) {
        texture = &map->imges[1];
    } else if (ray->west_face) {
        texture = &map->imges[2];
    } else if (ray->east_face) {
        texture = &map->imges[3];
    }

    // Ensure texture is valid
    if (!texture || !texture->addr) {
        printf("Error: Invalid texture or texture address.\n");
        return 0;
    }

    // Calculate the x coordinate on the texture
    text_off_x = offset_x(ray, texture);
    if (text_off_x < 0)
		text_off_x = 0;

    // Calculate the y coordinate on the texture
    factor = (double)texture->img_height / height;
	distance_from_top = y + (height / 2) - (SCREEN_HEIGHT / 2);
    text_off_y = distance_from_top * factor;
    if (text_off_y < 0) text_off_y = 0;

    // Ensure the texture coordinates are within bounds
    if (text_off_x >= texture->img_width || text_off_y >= texture->img_height) {
        printf("Error: Texture coordinates out of bounds. text_off_x = %f, text_off_y = %f\n", text_off_x, text_off_y);
        return 0;
    }

    // Get the color from the texture
    uint32_t *pixel = (uint32_t *)(texture->addr + (int)text_off_y * texture->line_length + (int)text_off_x * (texture->bits_per_pixel / 8));

    // Ensure pixel is within bounds of texture->addr
    if ((char *)pixel < texture->addr || (char *)pixel >= texture->addr + (texture->img_height * texture->line_length)) {
        printf("Error: Pixel address out of bounds.\n");
        return 0;
    }

    return *pixel;
}


static void draw_3dwall(t_map *map, int x, int top, int height)
{
	int y;
	int color;

	// Ensure the top is not above the screen
	// Ensure the bottom is not below the screen
	if (top + height > SCREEN_HEIGHT)
		height = SCREEN_HEIGHT - top;
	y = top;
	if (y < 0)
		y = 0;
	while(y < top + height)
	{
		if (y > SCREEN_HEIGHT)
			break;
		color = wall_texture(map, x, y, top, height);
		my_mlx_pixel_put(&map->img, x, y, color);
		y++;
	}


}

static void render3d(t_map *map)
{
	int i = 0;

	// double ray_angle = 0.0;
	double wall_strip_height;
	double ray_distance;
	double distance_projection_plane;
	while(i < NUM_RAYS)
	{
		ray_distance = map->distances[i] * cos(map->rays_ang[i] - map->rotation_angle);
		// ray_angle = map->rays_ang[i];
		distance_projection_plane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
		wall_strip_height = (TILE_SIZE / ray_distance) * distance_projection_plane;
		draw_3dwall(map, i, SCREEN_HEIGHT / 2 - wall_strip_height / 2, wall_strip_height);
		i++;
	}
}

int ft_render_the_game(t_map *map)
{

	ceiling_floor(map);
	mlx_clear_window(map->mlx, map->win);
	rays_handler(map);
	render3d(map);
	draw_map(map);

	// Cast rays and draw them
	mlx_put_image_to_window(map->mlx, map->win, map->img.img, 0, 0);
	return 0;
}

static int get_map_rows(char **map)
{
	int rows = 0;
	while (map[rows] != NULL) // Assuming the map is NULL-terminated
		rows++;
	return rows;
}
static int get_map_columns(char **map)
{
	int columns = 0;
	if (map[0] != NULL)
	{
		while (map[0][columns] != '\0')
			columns++;
	}
	return columns;
}

int	execution(t_map map)
{
	map.mlx = mlx_init();
	map.ray_angle = 30 * (PI / 180);
	map.imges[0].img = mlx_xpm_file_to_image(map.mlx, map.north_path, &map.imges[0].img_width, &map.imges[0].img_height);
	map.imges[0].addr = mlx_get_data_addr(map.imges[0].img, &map.imges[0].bits_per_pixel, &map.imges[0].line_length, &map.imges[0].endian);
	map.imges[1].img = mlx_xpm_file_to_image(map.mlx, map.south_path, &map.imges[1].img_width, &map.imges[1].img_height);
	map.imges[1].addr = mlx_get_data_addr(map.imges[1].img, &map.imges[1].bits_per_pixel, &map.imges[1].line_length, &map.imges[1].endian);
	map.imges[2].img = mlx_xpm_file_to_image(map.mlx, map.west_path, &map.imges[2].img_width, &map.imges[2].img_height);
	map.imges[2].addr = mlx_get_data_addr(map.imges[2].img, &map.imges[2].bits_per_pixel, &map.imges[2].line_length, &map.imges[0].endian);
	map.imges[3].img = mlx_xpm_file_to_image(map.mlx, map.east_path, &map.imges[3].img_width, &map.imges[3].img_height);
	map.imges[3].addr = mlx_get_data_addr(map.imges[3].img, &map.imges[3].bits_per_pixel, &map.imges[3].line_length, &map.imges[3].endian);
	map.win = mlx_new_window(map.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	map.img.img = mlx_new_image(map.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_hook(map.win, 17, 0, &close_window, &map);
	map.img.addr = mlx_get_data_addr(map.img.img,
			&map.img.bits_per_pixel, &map.img.line_length,
			&map.img.endian);
	find_player(&map);
	mlx_hook(map.win, 2, 0, key_hook, &map);
	map.height = get_map_rows(map.map);
	map.width = get_map_columns(map.map);
	printf("height = %d, width = %d\n", map.height, map.width);
	print_map(map.map);
	ft_render_the_game(&map);
	mlx_loop(map.mlx);
	return (0);
}
