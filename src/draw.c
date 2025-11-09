/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 01:40:09 by lomont            #+#    #+#             */
/*   Updated: 2025/11/09 01:05:35 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static uint32_t	texture_color(t_app *app, int i, int texY, int texX)
{
	uint8_t		*pixels;
	uint8_t		bytes_per_pixels;
	uint32_t	color;
	int			pixel_index;

	pixels = app->textures[i]->pixels;
	bytes_per_pixels = app->textures[i]->bytes_per_pixel;
	pixel_index = (texY * app->textures[i]->width + texX) * bytes_per_pixels;
	color = get_rgba(pixels[pixel_index], pixels[pixel_index + 1],
			pixels[pixel_index + 2], pixels[pixel_index + 3]);
	return (color);
}

static void	draw_texture(t_app *app)
{
	int		y;
	int		i;
	int		tex_y;
	int		tex_x;
	t_ray	*ray;

	ray = &app->ray;
	tex_x = ray->texture_x;
	i = ray->texture_index;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->texture_pos & (TEXTURE_HEIGHT - 1);
		ray->texture_pos += ray->step;
		mlx_put_pixel(app->img, app->x, y, texture_color(app, i, tex_y, tex_x));
		y++;
	}
}

static void	draw_floor(t_app *app)
{
	int			y;
	t_ray		*ray;
	uint32_t	floor;

	ray = &app->ray;
	floor = get_rgba(220, 100, 0, 255);
	y = ray->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		mlx_put_pixel(app->img, app->x, y, floor);
		y++;
	}
}

static void	draw_ceiling(t_app *app)
{
	int			y;
	t_ray		*ray;
	uint32_t	ceiling;

	ray = &app->ray;
	ceiling = get_rgba(225, 30, 0, 255);
	y = 0;
	while (y < ray->draw_start)
	{
		mlx_put_pixel(app->img, app->x, y, ceiling);
		y++;
	}
}

void	drawing(t_app *app)
{
	draw_ceiling(app);
	draw_floor(app);
	draw_texture(app);
}
