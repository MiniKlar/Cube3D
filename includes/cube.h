/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:38:27 by lomont            #+#    #+#             */
/*   Updated: 2025/11/13 16:42:38 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

# include "stdio.h"
# include "stdlib.h"
# include <math.h>
# include "../MLX42/mlx42.h"
# include "../LIB_C/LIB_C.h"

# ifndef SHOW_FPS
#  define SHOW_FPS 0
# endif

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1080
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 720
# endif

# ifndef TEXTURE_WIDTH
#  define TEXTURE_WIDTH 64
# endif

# ifndef TEXTURE_HEIGHT
#  define TEXTURE_HEIGHT 64
# endif

# ifndef CONFIG_COUNT
#  define CONFIG_COUNT 6
# endif

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	char	start_direction;
}				t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	double	perp_wall_dist;
	int		side;
	int		hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texture_index;
	int		texture_x;
	int		texture_y;
	double	step;
	double	texture_pos;
	double	wall_x;
}				t_ray;

typedef struct s_textures
{
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
}	t_textures;

typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
	uint32_t	color;
} t_rgb;

typedef struct s_app
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*fps;
	mlx_texture_t	*textures[4];
	uint32_t		ceiling;
	uint32_t		floor;
	int				fd;
	int				x;
	int				map_width;
	int				map_height;
	double			time;
	char			direction;
	char			**map;
	t_player		player;
	t_ray			ray;
	t_textures		tex;
	t_rgb			rgb;
}				t_app;

//EXEC

bool		init_app(t_app *app);
void		render(t_app *app);
void		drawing(t_app *app);
void		calcul_direction(t_app *app);
void		calcul_draw(t_app *app);
void		calcul_ray_direction_distance(t_app *app);
void		calcul_step_side_distance(t_app *app);
void		calcul_if_wall_hitted(t_app *app);
void		create_image(t_app *app);
void		clear_image(t_app *app);
void		frametime(t_app *app, int fps);
void		hook(void* param);
void		init_player_direction(t_app *app);
uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b);
bool		init_mlx(t_app *app);

//PARSING

// utils/..

int			is_only_digits(char *s);
bool		is_line_empty(char *line);
char		*strtrim_start(char *s);
size_t		array_len(char **tab);
void		free_tab(char **tab);

void		error_exit_1(t_app *app, char *msg, char **tab);
void		error_exit_2(t_app *app, char *msg, char **tab, char *tab_2);
void		error_exit_3(t_app *app, char **tab, char *tab_2, char *tab_3);
void		error_exit(t_app *app, char *msg);

void		free_app(t_app *app);

// config_validity/..

uint32_t	rgb_to_uint(t_app *app, char *rgb_str, char *trimmed);
bool		validate_color(t_app *app, char *rgb_str, char *trimmed);
bool		validate_texture(t_app *app, char *path_str, char *trimmed);

char		*get_clean_line(t_app *app, int fd, char **line_ptr);
int			extract_value(t_app *app, char *trimmed, int *count, bool valid);
char		*find_first_map_line(t_app *app, int fd);
char		*parse_config(t_app *app, int fd);

bool		cub_extension(char *file);
int			readable_map_file(char *file);

// map_validity/..

char		**copy_grid(t_app *app);
void		launch_flood_fill_from_player(t_app *app, char **grid);
void		flood_fill(t_app *app, char **grid, int x, int y);

bool		is_map_started(char **grid);
char		**realloc_grid(t_app *app, char **old_grid, int new_rows);
char		*strtrim_end_nl(char *line);

bool		is_valid_char(char c);
bool		is_player_char(char c);
void		set_player_pos(t_app *app, char **grid, int x, int y);

int			get_max_width(char **grid);
void		store_map(t_app *app, char **temp_grid, int rows);

char		**assemble_grid(t_app *app, int fd, char *first_line, int *rows);
void		validate_chars_and_player(t_app *app, char **grid, int rows);
void		check_map_closure(t_app *app);
void		parse_map(t_app *app, int fd, char *first_line_map);

// main

bool		parsing(t_app *app, char *file);

#endif
