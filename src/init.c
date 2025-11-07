/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:41:15 by lomont            #+#    #+#             */
/*   Updated: 2025/11/07 01:15:44 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

bool init_mlx(mlx_t **mlx)
{
	*mlx = mlx_init(1920, 1080, "Cube3D", true);
	if (!mlx)
		return (false);
	return (true);
}

bool init_app(t_app *app)
{
	if (app)
	{
		if (!init_mlx(&app->mlx))
			return (false);
		app->posX = 22;
		app->posY = 12;
		app->dirX = -1;
		app->dirY = 0;
		app->planeX = 0;
		app->planeY = 0.66;
		app->time = 0;
		app->move_speed = 0;
		app->rot_speed = 0;
		app->img = NULL;
		app->fps_img = NULL;
		app->textures[0] = NULL;
	}
	return (true);
}
