/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:25:00 by lomont            #+#    #+#             */
/*   Updated: 2025/11/06 06:13:07 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void draw_vertical_line(mlx_image_t* image, int x, int draw_start, int draw_end, int color);
void frametime(t_app *app);
void create_image(t_app *app);

int worldMap[24][24]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void render(t_app *app)
{
	int x = 0;

	while (x < 1920)
	{
		double cameraX = 2 * x / (double)1920 - 1;
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

		int line_height = (int)(1080 / perp_wall_dist);
		int draw_start = -line_height / 2 + 1080 / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + 1080 / 2;
		if (draw_end >= 1080)
			draw_end = 1080 - 1;

		int color;

		if (worldMap[mapX][mapY] == 1)
			color = 0xff0000ff;
		else if (worldMap[mapX][mapY] == 2)
			color = 0x4dff00ff;
		else if (worldMap[mapX][mapY] == 3)
			color = 0x1900ffff;
		else if (worldMap[mapX][mapY] == 4)
			color = 0xffffffff;
		else
			color = 0xffee00ff;

		if (side == 1)
			color = color / 2;

		draw_vertical_line(app->img, x, draw_start, draw_end, color);
		x++;
	}
}

bool init_mlx(mlx_t **mlx)
{
	*mlx = mlx_init(1920, 1080, "Cube3D", true);
	if (!mlx)
		return (false);
	return (true);
}

bool init_app(t_app *app)
{
	if (app)
	{
		if (!init_mlx(&app->mlx))
			return (false);
		app->posX = 22;
		app->posY = 12;
		app->dirX = -1;
		app->dirY = 0;
		app->planeX = 0;
		app->planeY = 0.66;
		app->time = 0;
		app->move_speed = 0;
		app->rot_speed = 0;
		app->img = NULL;
		app->fps = NULL;
	}
	return (true);
}

void draw_vertical_line(mlx_image_t* image, int x, int draw_start, int draw_end, int color)
{
    int y = draw_start;
    while (y <= draw_end)
    {
        if (x >= 0 && x < (int)image->width && y >= 0 && y < (int)image->height)
        {
            mlx_put_pixel(image, x, y, color);
        }
        y++;
    }
}

void clear_image(t_app *app)
{
	ft_memset(app->img->pixels, 0, app->img->width * app->img->height * sizeof(int32_t));
}

void key_pressed(void* param)
{
	t_app *app;

	app = param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
	if (mlx_is_key_down(app->mlx, MLX_KEY_W) || mlx_is_key_down(app->mlx, MLX_KEY_UP))
	{
		if (!worldMap[(int)(app->posX + app->dirX * app->move_speed)][(int)app->posY])
			app->posX += app->dirX * app->move_speed;
		if (!worldMap[(int)app->posX][(int)(app->posY + app->dirY * app->move_speed)])
			app->posY += app->dirY * app->move_speed;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_S) || mlx_is_key_down(app->mlx, MLX_KEY_DOWN))
	{
		if (!worldMap[(int)(app->posX - app->dirX * app->move_speed)][(int)app->posY])
			app->posX -= app->dirX * app->move_speed;
		if (!worldMap[(int)(app->posX)][(int)(app->posY - app->dirY * app->move_speed)])
			app->posY -= app->dirY * app->move_speed;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = app->dirX;
		app->dirX = app->dirX * cos(-(app->rot_speed)) - app->dirY * sin(-(app->rot_speed));
		app->dirY = oldDirX * sin(-(app->rot_speed)) + app->dirY * cos(-(app->rot_speed));
		double oldPlaneX = app->planeX;
		app->planeX = app->planeX * cos((-app->rot_speed)) - app->planeY * sin(-(app->rot_speed));
		app->planeY = oldPlaneX * sin(-(app->rot_speed)) + app->planeY * cos(-app->rot_speed);
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = app->dirX;
		app->dirX = app->dirX * cos(app->rot_speed) - app->dirY * sin(app->rot_speed);
		app->dirY = oldDirX * sin(app->rot_speed) + app->dirY * cos(app->rot_speed);
		double oldPlaneX = app->planeX;
		app->planeX = app->planeX * cos(app->rot_speed) - app->planeY * sin(app->rot_speed);
		app->planeY = oldPlaneX * sin(app->rot_speed) + app->planeY * cos(app->rot_speed);
	}
	clear_image(app);
	render(app);
	frametime(app);
}

void frametime(t_app *app)
{
	char	*fps_str;
	char	*tmp;
	double old_time = app->time;

	if (app->fps)
		mlx_delete_image(app->mlx, app->fps);
	app->time = mlx_get_time();
	double frame_time = (app->time - old_time);
	app->move_speed = 0.05;
	app->rot_speed = 0.03;
	int fps = (1.0 / frame_time);
	if (SHOW_FPS)
	{
		tmp = ft_itoa(fps);
		fps_str = ft_strjoin("FPS = ", tmp);
		app->fps = mlx_put_string(app->mlx, fps_str, 0, 0);
		free(tmp);
		free(fps_str);
	}
}

void create_image(t_app *app)
{
	app->img = mlx_new_image(app->mlx, 1920, 1080);
	if (!app->img || (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0))
		exit(1);
}

int	main(void)
{
	t_app app;

	if (!init_app(&app))
		return (1);

	create_image(&app);
	mlx_loop_hook(app.mlx, &key_pressed, &app);
	mlx_loop(app.mlx);
	mlx_terminate(app.mlx);
	return (0);
}
