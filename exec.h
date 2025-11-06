/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:25:26 by lomont            #+#    #+#             */
/*   Updated: 2025/11/06 06:10:41 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#include "MLX42/mlx42.h"
#include "LIB_C/LIB_C.h"

#ifndef SHOW_FPS
# define SHOW_FPS 0
#endif

typedef struct s_app
{
	mlx_t *mlx;
	mlx_image_t* img;
	mlx_image_t* fps;
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

#endif
