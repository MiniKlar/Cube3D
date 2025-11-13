/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calcul.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:18:02 by lomont            #+#    #+#             */
/*   Updated: 2025/11/13 03:54:10 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cube.h"

void	calcul_if_wall_hitted(t_app *app)
{
	t_ray	*ray;

	ray = &app->ray;
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (app->map[ray->map_y][ray->map_x] > 48)
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_y);
}

void	calcul_step_side_distance(t_app *app)
{
	t_ray		*ray;
	t_player	*player;

	ray = &app->ray;
	player = &app->player;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	}
}

void	calcul_ray_direction_distance(t_app *app)
{
	t_ray		*ray;
	t_player	*player;

	ray = &app->ray;
	player = &app->player;
	ray->camera_x = 2 * app->x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->ray_dir_y);
}

void	calcul_draw(t_app *app)
{
	t_ray	*ray;

	ray = &app->ray;
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

void	calcul_direction(t_app *app)
{
	int		i;
	t_ray	*ray;

	ray = &app->ray;
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			i = 0;
		else
			i = 3;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			i = 2;
		else
			i = 1;
	}
	ray->texture_index = i;
}
