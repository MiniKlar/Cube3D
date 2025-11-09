/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:25:26 by lomont            #+#    #+#             */
/*   Updated: 2025/11/09 03:00:27 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "stdio.h"
# include "stdlib.h"
# include <math.h>
# include "../MLX42/mlx42.h"
# include "../LIB_C/LIB_C.h"

# ifndef SHOW_FPS
#  define SHOW_FPS 0
# endif

# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 1920
# endif

# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 1080
# endif

# ifndef TEXTURE_WIDTH
#  define TEXTURE_WIDTH 64
# endif

# ifndef TEXTURE_HEIGHT
#  define TEXTURE_HEIGHT 64
# endif

extern int	worldMap[24][24];

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

typedef struct s_app
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[4];
	int				x;
	uint32_t		ceiling;
	uint32_t		floor;
	t_player		player;
	t_ray			ray;
}				t_app;

u_int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
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
void		hook(void* param);

#endif
