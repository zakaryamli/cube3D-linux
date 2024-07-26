/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyamli <zakariayamli@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:44:33 by zyamli            #+#    #+#             */
/*   Updated: 2024/07/20 19:13:45 by zyamli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_HEIGHT 720
# define SCREEN_WIDTH 1080
# define MINIMAP_WIDTH 275
# define MINIMAP_HEIGHT 275

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define BLACK 0x000000
# define GREEN 0x2F5233
# define BLUE 0x0000FF
# define PI 3.1415926535


# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "/home/yel-khad/Desktop/minilib/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <float.h>
# include <stdint.h>

#define FOV (40 * (PI / 180))
#define NUM_RAYS (int)(SCREEN_WIDTH / 1)
#define TILE_SIZE 10



typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	int		img_width;
	int		img_height;
}				t_data;
typedef struct s_ray
{
	double angle;
	double h_wall_hit_x;
	double h_wall_hit_y;
	double v_wall_hit_x;
	double v_wall_hit_y;
	double next_horiz_touch_x;
	double next_horiz_touch_y;
	double next_vert_touch_x;
	double next_vert_touch_y;
	double distance;
	double intercect1_x;
	double intercect1_y;
	double dx;
	double dy;
	bool ray_down;
	bool ray_up;
	bool ray_left;
	bool ray_right;
	bool horiz_wall_hit;
	bool vert_wall_hit;
	bool north_face;
	bool south_face;
	bool east_face;
	bool west_face;
} t_ray;

typedef struct s_map
{
	t_data		img;
	int			height;
	int			width;
	void		*mlx;
	void		*win;
	void		*north;
	void		*south;
	void		*west;
	void		*east;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	int			floor[3];
	int			ceiling[3];
	char		**map;
	double		*rays_ang;
	double		*distances;
	double		mini_x;
	double		mini_y;
	double		my;
	double		mx;
	double		player_x;
	double		player_y;
	double		position_x;
	double		position_y;
	char		direction;
	double		ray_angle;
	double		rotation_angle;
	double		rotation_speed;
	t_ray		*ray;
	t_data		imges[4];
}	t_map;

typedef struct s_parsing
{
	int	addmorelater;
}	t_parsing;

typedef struct s_mapheader
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	c;
	int	f;
}	t_mapheader;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

//parsing tools
int		check_name(char *str);
int		check_map(t_map *map, char *map_name);
char	**readfilecontant(char *mapname, int fd, int len, int i);
int		check_texture_and_colors(t_map *map, char **map_contant, int *i);
int		check_map_contant(t_map *map, char **map_contant, int i);
int		is_only_map(char **map, int i);
int		search_line(char *str, char *look);
char	**get_only_map(char **map, int i);
int		map_size(char **map, int i);
char	**make_it_bigger_square(char **map, int x, int y, int i);
int		get_biggest_x(char **map);
int		get_biggest_y(char **map);
char	*fill_it2(int x);
char	*fill_it1(char **map, int x, int y);
char	**create_cpy(char **map);
int		check_characters(char **map);
void	can_access(char **map, int x, int y, t_point limit);
void	only1player(char **map, t_map *info, int y, int x);
void	can_fall(char **map, int x, int y, t_point limit);
int		get_biggest_x2(char **map, t_map *info);
int		get_biggest_y2(char **map, t_map *info);
void	basic_init(t_mapheader *mapheader);
int		valid_colors(t_map *map, char *str, int f_or_c);
int		check_colors(t_map *map, char *line, t_mapheader *mapheader, int *i);
int		path_exist(t_map *map, char *str, int direction);
int		check_texture(t_map *map, char *line, t_mapheader *mapheader, int *i);
int		check_line(t_map *map, char *line, t_mapheader *mapheader, int i);
void	calc_minimap(t_map *map);

//execution tools
int		key_hook(int keycode, t_map *map);
int		close_window(t_map *info);
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_render_the_game(t_map *map);
void	put_player(t_map *info);
void	put_minimap(t_map *map);
void	put_map(t_map *map);
int		execution(t_map map);

//general tools
int		ft_isnum(char *str);
char	*ft_strchr(char *str, char c);
int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(char *arg);
int		ft_is_space(char c);
int		ft_strcmp(char *str1, char *str2);
int		parsing(t_map *map, char *map_name);
int		execution(t_map map);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *s);
char	*ft_strchr(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoinx(char *remain, char *buffer);
char	*get_next_line(int fd);
int		get_lines(int fd);
int		stop_here2(char *str);
int		is_wall(t_map *map, double x, double y);
// void	draw_line(t_map *map, int x0, int y0, int x1, int y1, int color);


//errors
void	error1(void);
void	error2(void);
void	error3(void);
void	error4(void);
void	error5(void);
void	error43(void);
void	error_player(void);

//printing
void	print_map(char **map);

#endif
