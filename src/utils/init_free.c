/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:42:58 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/11 16:12:50 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
