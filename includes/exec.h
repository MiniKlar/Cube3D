/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:25:26 by lomont            #+#    #+#             */
/*   Updated: 2025/11/07 01:25:48 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#include "../MLX42/mlx42.h"
#include "../LIB_C/LIB_C.h"

#ifndef SHOW_FPS
# define SHOW_FPS 0
#endif

#ifndef SCREEN_WIDTH
#	define SCREEN_WIDTH 1920
#endif

#ifndef SCREEN_HEIGHT
#	define SCREEN_HEIGHT 1080
#endif

#ifndef TEXTURE_WIDTH
#	define TEXTURE_WIDTH 64
#endif

#ifndef TEXTURE_HEIGHT
#	define TEXTURE_HEIGHT 64
#endif

extern int worldMap[24][24];

typedef struct s_app
{
	mlx_t *mlx;
	mlx_image_t* img;
	mlx_image_t* fps_img;
	mlx_texture_t* textures[4];
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double move_speed;
	double rot_speed;
}				t_app;

bool init_mlx(mlx_t **mlx);
bool init_app(t_app *app);
void render(t_app *app);

#endif
