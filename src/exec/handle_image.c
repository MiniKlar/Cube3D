/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 06:20:36 by lomont            #+#    #+#             */
/*   Updated: 2025/11/17 00:19:15 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	create_image(t_app *app)
{
	app->img = mlx_new_image(app->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!app->img)
		free_error_mlx(app);
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		free_error_mlx(app);
	app->textures[0] = mlx_load_png(app->tex.east_path);
	app->textures[1] = mlx_load_png(app->tex.north_path);
	app->textures[2] = mlx_load_png(app->tex.south_path);
	app->textures[3] = mlx_load_png(app->tex.west_path);
	if (!app->textures[0] || !app->textures[1] || !app->textures[2]
		|| !app->textures[3])
		free_error_mlx(app);
}

void	clear_image(t_app *app)
{
	mlx_image_t	*img;

	img = app->img;
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
}
