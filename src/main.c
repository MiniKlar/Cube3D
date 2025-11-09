/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:25:00 by lomont            #+#    #+#             */
/*   Updated: 2025/11/09 01:11:53 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int worldMap[24][24]=
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void key_pressed(void* param)
{
	t_app		*app;
	t_player	*player;

	app = param;
	player = &app->player;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
	if (mlx_is_key_down(app->mlx, MLX_KEY_W))
	{
		if (!worldMap[(int)(player->pos_x + player->dir_x * player->move_speed)][(int)player->pos_y])
			player->pos_x += player->dir_x * player->move_speed;
		if (!worldMap[(int)player->pos_x][(int)(player->pos_y + player->dir_y * player->move_speed)])
			player->pos_y += player->dir_y * player->move_speed;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_D))
	{
		if (!worldMap[(int)(player->pos_x + player->plane_x * player->move_speed)][(int)player->pos_y])
			player->pos_x += player->plane_x * player->move_speed;
		if (!worldMap[(int)player->pos_x][(int)(player->pos_y + player->plane_y * player->move_speed)])
			player->pos_y += player->plane_y * player->move_speed;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_Q))
	{
		if (!worldMap[(int)(player->pos_x - player->plane_x * player->move_speed)][(int)player->pos_y])
			player->pos_x -= player->plane_x * player->move_speed;
		if (!worldMap[(int)(player->pos_x)][(int)(player->pos_y - player->plane_y * player->move_speed)])
			player->pos_y -= player->plane_y * player->move_speed;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(-(player->rot_speed)) - player->dir_y * sin(-(player->rot_speed));
		player->dir_y = oldDirX * sin(-(player->rot_speed)) + player->dir_y * cos(-(player->rot_speed));
		double oldPlaneX = player->plane_x;
		player->plane_x = player->plane_x * cos((-player->rot_speed)) - player->plane_y * sin(-(player->rot_speed));
		player->plane_y = oldPlaneX * sin(-(player->rot_speed)) + player->plane_y * cos(-player->rot_speed);
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = player->dir_x;
		player->dir_x = player->dir_x * cos(player->rot_speed) - player->dir_y * sin(player->rot_speed);
		player->dir_y = oldDirX * sin(player->rot_speed) + player->dir_y * cos(player->rot_speed);
		double oldPlaneX = player->plane_x;
		player->plane_x = player->plane_x * cos(player->rot_speed) - player->plane_y * sin(player->rot_speed);
		player->plane_y = oldPlaneX * sin(player->rot_speed) + player->plane_y * cos(player->rot_speed);
	}
	clear_image(app);
	render(app);
	//frametime(app);
}

int	main(void)
{
	t_app	app;

	if (!init_app(&app))
		return (1);
	create_image(&app);
	mlx_loop_hook(app.mlx, &key_pressed, &app);
	mlx_loop(app.mlx);
	mlx_terminate(app.mlx);
	return (0);
}
