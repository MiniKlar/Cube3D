/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:40:56 by lomont            #+#    #+#             */
/*   Updated: 2025/11/07 03:56:08 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

uint32_t texture_color(t_app *app, int i, int texY, int texX)
{
	uint32_t color;
	int first_index = (texY * app->textures[i]->width + texX) * app->textures[i]->bytes_per_pixel;
	color = (app->textures[i]->pixels[first_index] << 24) |
		(app->textures[i]->pixels[first_index + 1] << 16) |
		(app->textures[i]->pixels[first_index + 2] << 8) |
		(app->textures[i]->pixels[first_index + 3]);
	return (color);
}

void render(t_app *app)
{
	int x = 0;

	while (x < SCREEN_WIDTH)
	{
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		double ray_dir_x = app->dirX + app->planeX * cameraX;
		double ray_dir_y = app->dirY + app->planeY * cameraX;

		int mapX = (int)app->posX;
		int mapY = (int)app->posY;

		double side_dist_x;
		double side_dist_y;

		double delta_dist_x;
		double delta_dist_y;

		double perp_wall_dist;

		if (ray_dir_x == 0)
			delta_dist_x = 1e30;
		else
			delta_dist_x = fabs(1 / ray_dir_x);

		if (ray_dir_y == 0)
			delta_dist_y = 1e30;
		else
			delta_dist_y = fabs(1 / ray_dir_y);

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (ray_dir_x < 0)
		{
			stepX = -1;
			side_dist_x = (app->posX - mapX) * delta_dist_x;
		}
		else
		{
			stepX = 1;
			side_dist_x = (mapX + 1.0 - app->posX) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			stepY = -1;
			side_dist_y = (app->posY - mapY) * delta_dist_y;
		}
		else
		{
			stepY = 1;
			side_dist_y = (mapY + 1.0 - app->posY) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				mapX += stepX;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;


		//calculer dans une fonction à part
		int index_to_use = -1;
		if (side == 0 && ray_dir_x > 0)
			index_to_use = 0;
		else if (side == 0 && ray_dir_x < 0)
			index_to_use = 3;
		else if (side == 1 && ray_dir_y > 0)
			index_to_use = 2;
		else if (side == 1 && ray_dir_y < 0)
			index_to_use = 1;

		double wallX;
		if (side == 0)
			wallX = app->posY + perp_wall_dist * ray_dir_y;
		else
			wallX = app->posX + perp_wall_dist * ray_dir_x;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)TEXTURE_WIDTH);
		if(side == 0 && ray_dir_x > 0) texX = TEXTURE_WIDTH - texX - 1;
		if(side == 1 && ray_dir_y < 0) texX = TEXTURE_WIDTH - texX - 1;

		double step = 1.0 * TEXTURE_HEIGHT / line_height;
		double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;

		int y = 0;
		while (y < draw_start)
		{
			uint32_t ceilling = (255 << 24) | 255; // Exemple couleur orange
			mlx_put_pixel(app->img, x, y, ceilling);
			y++;
		}
		y = draw_end + 1;
		while (y < SCREEN_HEIGHT)
		{
			uint32_t floor = (255 << 16) | 255; // Exemple couleur bleu-vert
			mlx_put_pixel(app->img, x, y, floor);
			y++;
		}

		y = draw_start;
		while (y < draw_end)
		{
			int texY = (int)tex_pos & (TEXTURE_HEIGHT - 1);
			tex_pos += step;
			mlx_put_pixel(app->img, x, y, texture_color(app, index_to_use, texY, texX));
			y++;
		}
		x++;
	}
}
