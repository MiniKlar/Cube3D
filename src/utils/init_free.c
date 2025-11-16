/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:42:58 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/17 00:18:41 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	free_mlx_texture(mlx_texture_t *textures[4])
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (textures[i])
			mlx_delete_texture(textures[i]);
		i++;
	}
	return ;
}

void	free_error_mlx(t_app *app)
{
	mlx_t	*mlx;

	mlx = app->mlx;
	mlx_close_window(mlx);
	mlx_terminate(mlx);
	free_app(app);
	ft_putendl_fd("Error MLX", 2);
	exit(1);
}

void	free_app(t_app *app)
{
	int	i;

	i = 0;
	if (app->tex.north_path)
		free(app->tex.north_path);
	if (app->tex.south_path)
		free(app->tex.south_path);
	if (app->tex.east_path)
		free(app->tex.east_path);
	if (app->tex.west_path)
		free(app->tex.west_path);
	free_mlx_texture(app->textures);
	if (app->map)
	{
		while (i < app->map_height)
		{
			if (app->map[i])
				free(app->map[i]);
			i++;
		}
		free(app->map);
	}
}
