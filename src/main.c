/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:25:00 by lomont            #+#    #+#             */
/*   Updated: 2025/11/07 02:25:21 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

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

void frametime(t_app *app);
void create_image(t_app *app);

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
	if (mlx_is_key_down(app->mlx, MLX_KEY_D))
	{
		if (!worldMap[(int)(app->posX + app->planeX * app->move_speed)][(int)app->posY])
			app->posX += app->planeX * app->move_speed;
		if (!worldMap[(int)app->posX][(int)(app->posY + app->planeY * app->move_speed)])
			app->posY += app->planeY * app->move_speed;
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_Q))
	{
		if (!worldMap[(int)(app->posX - app->planeX * app->move_speed)][(int)app->posY])
			app->posX -= app->planeX * app->move_speed;
		if (!worldMap[(int)(app->posX)][(int)(app->posY - app->planeY * app->move_speed)])
			app->posY -= app->planeY * app->move_speed;
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

	if (app->fps_img)
		mlx_delete_image(app->mlx, app->fps_img);
	app->time = mlx_get_time();
	double frame_time = (app->time - old_time);
	app->move_speed = 0.05;
	app->rot_speed = 0.03;
	int fps = (1.0 / frame_time);
	if (SHOW_FPS)
	{
		tmp = ft_itoa(fps);
		fps_str = ft_strjoin("FPS = ", tmp);
		app->fps_img = mlx_put_string(app->mlx, fps_str, 0, 0);
		free(tmp);
		free(fps_str);
	}
}

void create_image(t_app *app)
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
