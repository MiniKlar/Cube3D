/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 06:20:36 by lomont            #+#    #+#             */
/*   Updated: 2025/11/09 01:13:10 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	create_image(t_app *app)
{
	app->img = mlx_new_image(app->mlx, 1920, 1080);
	if (!app->img || (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0))
		exit(1);
	app->textures[0] = mlx_load_png("./models/east_model.png");
	if (!app->textures[0])
		exit(2);
	app->textures[1] = mlx_load_png("./models/north_model.png");
	if (!app->textures[1])
		exit(3);
	app->textures[2] = mlx_load_png("./models/south_model.png");
	if (!app->textures[2])
		exit(4);
	app->textures[3] = mlx_load_png("./models/west_model.png");
	if (!app->textures[3])
		exit(5);
}

void	clear_image(t_app *app)
{
	mlx_image_t	*img;

	img = app->img;
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
}
