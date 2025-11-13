/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 01:09:03 by lomont            #+#    #+#             */
/*   Updated: 2025/11/11 15:47:23 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	frametime(t_app *app, int fps)
{
	double	old_time;
	double	frame_time;
	char	*fps_str;
	char	*tmp;

	if (app->fps)
		mlx_delete_image(app->mlx, app->fps);
	old_time = app->time;
	app->time = mlx_get_time();
	frame_time = (app->time - old_time);
	fps = (1.0 / frame_time);
	if (SHOW_FPS)
	{
		tmp = ft_itoa(fps);
		fps_str = ft_strjoin("FPS = ", tmp);
		app->fps = mlx_put_string(app->mlx, fps_str, 0, 0);
		free(tmp);
		free(fps_str);
	}
}
