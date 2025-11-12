/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:41:15 by lomont            #+#    #+#             */
/*   Updated: 2025/11/12 04:38:52 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	set_player_no_so_position(t_app *app, t_player *player)
{
	if (app->direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1.0;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (app->direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1.0;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
}

void	init_player_direction(t_app *app)
{
	t_player	*player;

	player = &app->player;
	set_player_no_so_position(app, player);
	if (app->direction == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (app->direction == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	player->move_speed = 0.05;
	player->rot_speed = 0.03;
}

bool	init_mlx(t_app *app)
{
	app->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cube3D", true);
	if (!app->mlx){
		return (false);
	}
	return (true);
}

bool	init_app(t_app *app)
{
	if (!app)
		return (false);
	ft_bzero(app, sizeof(t_app));
	app->time = mlx_get_time();
	return (true);
}
