/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:41:15 by lomont            #+#    #+#             */
/*   Updated: 2025/11/09 01:03:30 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

static void	init_player(t_player *player)
{
	player->pos_x = 22;
	player->pos_y = 12;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->move_speed = 0.05;
	player->rot_speed = 0.03;
}

static bool	init_mlx(t_app *app)
{
	app->mlx = mlx_init(1920, 1080, "Cube3D", true);
	if (!app->mlx)
		return (false);
	return (true);
}

bool	init_app(t_app *app)
{
	if (!app)
		return (false);
	ft_bzero(app, sizeof(t_app));
	if (!init_mlx(app))
		return (false);
	init_player(&app->player);
	return (true);
}
