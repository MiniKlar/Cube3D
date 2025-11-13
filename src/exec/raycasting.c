/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:40:56 by lomont            #+#    #+#             */
/*   Updated: 2025/11/11 15:47:23 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	calcul_texture_output(t_app *app)
{
	t_ray		*ray;
	t_player	*player;

	ray = &app->ray;
	player = &app->player;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->texture_x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->texture_x = TEXTURE_WIDTH - ray->texture_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->texture_x = TEXTURE_WIDTH - ray->texture_x - 1;
	ray->step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	ray->texture_pos = (ray->draw_start - SCREEN_HEIGHT / 2
			+ ray->line_height / 2) * ray->step;
}

void	render(t_app *app)
{
	app->x = 0;
	while (app->x < SCREEN_WIDTH)
	{
		calcul_ray_direction_distance(app);
		calcul_step_side_distance(app);
		calcul_if_wall_hitted(app);
		calcul_draw(app);
		calcul_direction(app);
		calcul_texture_output(app);
		drawing(app);
		app->x++;
	}
}
