/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_fullfill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:11 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/13 17:37:14 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	**copy_grid(t_app *app)
{
	char	**test_grid;
	int		y;

	test_grid = ft_calloc(app->map_height + 1, sizeof(char *));
	if (!test_grid)
		error_exit(app, "Grid copy memory fail.");
	y = 0;
	while (y < app->map_height)
	{
		test_grid[y] = ft_strdup(app->map[y]);
		if (!test_grid[y])
			error_exit_1(app, "Grid row copy memory fail.", test_grid);
		y++;
	}
	return (test_grid);
}

void	launch_flood_fill_from_player(t_app *app, char **grid)
{
	int	start_x;
	int	start_y;

	start_x = (int)app->player.pos_x;
	start_y = (int)app->player.pos_y;
	if (start_y < 0 || start_y >= app->map_height)
		error_exit_1(app, "Player start Y is out of map.", grid);
	if (start_x < 0 || start_x >= (int)ft_strlen(grid[start_y]))
		error_exit_1(app, "Player start X is out of map.", grid);
	flood_fill(app, grid, start_x, start_y);
}

void	flood_fill(t_app *app, char **grid, int x, int y)
{
	int	max_x;
	int	max_y;

	max_y = app->map_height;
	max_x = ft_strlen(grid[y]);
	if (y < 0 || y >= max_y || x < 0 || x >= max_x)
		error_exit_1(app, "Map is not fully enclosed.", grid);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	if (grid[y][x] == ' ')
		error_exit_1(app, "Player's room touches empty space.", grid);
	if (grid[y][x] == '0')
		grid[y][x] = 'V';
	else
		return ;
	flood_fill(app, grid, x + 1, y);
	flood_fill(app, grid, x - 1, y);
	flood_fill(app, grid, x, y + 1);
	flood_fill(app, grid, x, y - 1);
}
