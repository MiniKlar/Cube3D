/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_fullfill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:11 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/10 18:41:55 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	**copy_grid(t_data *data)
{
	char	**test_grid;
	int		y;

	test_grid = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!test_grid)
		error_exit(data, "Grid copy memory fail.");
	y = 0;
	while (y < data->map_height)
	{
		test_grid[y] = ft_strdup(data->map[y]);
		if (!test_grid[y])
		{
			free_tab(test_grid);
			error_exit(data, "Grid row copy memory fail.");
		}
		y++;
	}
	return (test_grid);
}

void	launch_flood_fill_from_player(t_data *data, char **grid)
{
	int	start_x;
	int	start_y;

	start_x = (int)data->player.pos_x;
	start_y = (int)data->player.pos_y;
	if (start_y < 0 || start_y >= data->map_height)
	{
		free_tab(grid);
		error_exit(data, "Player start Y is out of map bounds.");
	}
	if (start_x < 0 || start_x >= (int)ft_strlen(grid[start_y]))
	{
		free_tab(grid);
		error_exit(data, "Player start X is out of map bounds.");
	}
	if (grid[start_y][start_x] == '1')
	{
		free_tab(grid);
		error_exit(data, "Player starts inside a wall.");
	}
	flood_fill(data, grid, start_x, start_y);
}

void	flood_fill(t_data *data, char **grid, int x, int y)
{
	int max_x;
	int max_y;

	max_y = data->map_height;
	max_x = ft_strlen(grid[y]);
	if (y < 0 || y >= max_y || x < 0 || x >= max_x)
	{
		free_tab(grid);
		error_exit(data, "Map is not fully enclosed.");
	}
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	if (grid[y][x] == ' ')
	{
		free_tab(grid);
		error_exit(data, "Player's room touches empty space.");
	}
	if (grid[y][x] == '0')
		grid[y][x] = 'V';
	else
		return;
	flood_fill(data, grid, x + 1, y);
	flood_fill(data, grid, x - 1, y);
	flood_fill(data, grid, x, y + 1);
	flood_fill(data, grid, x, y - 1);
}
