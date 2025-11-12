/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:43:02 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/12 22:01:02 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	parsing(t_app *app, char *file)
{
	int		fd;
	char	*first_line_map;

	if (!cub_extension(file))
		error_exit(app, "File must end with <.cub>", -1);
	fd = readable_map_file(file);
	app->fd = fd;
	first_line_map = parse_config(app, fd);
	if (!first_line_map)
		error_exit(app, "The map is missing after the configuration", fd);
	parse_map(app, fd, first_line_map);
	close(fd);
	return (0);
}

void	print_map(t_app *app)
{
	int	y;

	printf("--- MAP DEBUG PRINT ---\n");
	printf("Dimensions: %d x %d (Width x Height)\n",
		app->map_width, app->map_height);
	printf("Player Start Pos: (%.1f, %.1f) Direction: %c\n",
		app->player.pos_x, app->player.pos_y, app->player.start_direction);
	printf("\n");
	y = 0;
	if (!app->map)
	{
		printf("Error: Map grid is NULL.\n");
		return ;
	}
	while (app->map[y])
	{
		printf("[%02d] %s\n", y, app->map[y]);
		y++;
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	t_app	app;

	if (ac == 2)
	{
		if (!init_app(&app))
			return (1);
		if (!parsing(&app, av[1]))
		{
			print_map(&app);
			if (init_mlx(&app))
			{
				init_player_direction(&app);
				create_image(&app);
				mlx_loop_hook(app.mlx, &hook, &app);
				mlx_loop(app.mlx);
				mlx_terminate(app.mlx);
			}
		}
	}
	else
		return (ft_printf("Error : Usage : ./Cube3d <map.cub>\n"), 1);
	free_app(&app);
	return (0);
}
