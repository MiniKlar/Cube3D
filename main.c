/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:25:00 by lomont            #+#    #+#             */
/*   Updated: 2025/11/04 19:17:45 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "MLX42/mlx42.h"
#include "LIB_C/LIB_C.h"
#include <math.h>

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

void key_pressed(void* param)
{
	mlx_t *mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		ft_putendl_fd("Gotta go up!!", 1);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		ft_putendl_fd("Gotta go down!!", 1);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		ft_putendl_fd("Gotta go right!!", 1);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		ft_putendl_fd("Gotta go left!!", 1);
	return ;
}

int	main(void)
{
	mlx_t *mlx;
	double posX = 22, posY = 12;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;

	double time = 0;
	double old_time = 0;

	mlx = mlx_init(1920, 1080, "Cube3D", true);
	if (!mlx)
		return (1);

	mlx_image_t* img = mlx_new_image(mlx, 1920, 1080);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (2);

	int x = 0;
	while (x < 1920)
	{
		double cameraX = 2 * x / (double)1920 - 1;
		double ray_dir_x = dirX + planeX * cameraX;
		double ray_dir_y = dirY + planeY * cameraX;

		int mapX = (int)posX;
		int mapY = (int)posY;

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
			side_dist_x = (posX - mapX) * delta_dist_x;
		}
		else
		{
			stepX = 1;
			side_dist_x = (posX + 1.0 - mapX) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			stepY = -1;
			side_dist_y = (posY - mapY) * delta_dist_y;
		}
		else
		{
			stepY = 1;
			side_dist_y = (posY + 1.0 - mapY) * delta_dist_y;
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

		draw_vertical_line(img, x, draw_start, draw_end, color);
		x++;
	}

	old_time = time;

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_loop_hook(mlx, &key_pressed, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
