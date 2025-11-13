/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 02:57:02 by lomont            #+#    #+#             */
/*   Updated: 2025/11/13 11:05:45 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	handle_left_right_keys(mlx_t *mlx, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rot_speed = player->rot_speed;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rot_speed = -player->rot_speed;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y
		* sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y
		* sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y
		* cos(rot_speed);
}

static void	handle_q_d_keys(char **map, mlx_t *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (map[(int)player->pos_y][(int)(player->pos_x + player->plane_x
			* player->move_speed)] == 48)
			player->pos_x += player->plane_x * player->move_speed;
		if (map[(int)(player->pos_y + player->plane_y
				* player->move_speed)][(int)player->pos_x] == 48)
			player->pos_y += player->plane_y * player->move_speed;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (map[(int)player->pos_y][(int)(player->pos_x - player->plane_x
			* player->move_speed)] == 48)
			player->pos_x -= player->plane_x * player->move_speed;
		if (map[(int)(player->pos_y - player->plane_y
				* player->move_speed)][(int)player->pos_x] == 48)
			player->pos_y -= player->plane_y * player->move_speed;
	}
}

static void	handle_w_s_keys(char **map, mlx_t *mlx, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (map[(int)player->pos_y][(int)(player->pos_x + player->dir_x
			* player->move_speed)] == 48)
			player->pos_x += player->dir_x * player->move_speed;
		if (map[(int)(player->pos_y + player->dir_y
				* player->move_speed)][(int)player->pos_x] == 48)
			player->pos_y += player->dir_y * player->move_speed;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (map[(int)player->pos_y][(int)(player->pos_x - player->dir_x
			* player->move_speed)] == 48)
			player->pos_x -= player->dir_x * player->move_speed;
		if (map[(int)(player->pos_y - player->dir_y
				* player->move_speed)][(int)player->pos_x] == 48)
			player->pos_y -= player->dir_y * player->move_speed;
	}
}

void	hook(void *param)
{
	t_app		*app;
	t_player	*player;

	app = param;
	player = &app->player;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
	handle_w_s_keys(app->map, app->mlx, player);
	handle_q_d_keys(app->map, app->mlx, player);
	handle_left_right_keys(app->mlx, player);
	clear_image(app);
	render(app);
	frametime(app, 0);
}
