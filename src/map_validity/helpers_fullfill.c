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
	int	max_x;
	int	max_y;

	start_x = (int)data->player.pos_x;
	start_y = (int)data->player.pos_y;
	max_x = data->map_width;
	max_y = data->map_height;
	if (start_x < 0 || start_x >= max_x || start_y < 0 || start_y >= max_y)
		error_exit(data, "Player start position is out of map bounds.");
	if (grid[start_y][start_x] == '1')
		error_exit(data, "Player starts inside a wall.");
	flood_fill(data, grid, start_x, start_y, max_x, max_y);
}

void	flood_fill(t_data *data, char **grid, int x, int y, int max_x, int max_y)
{
	if (x < 0 || x >= max_x || y < 0 || y >= max_y)
		error_exit(data, "Map is not fully enclosed.");
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	if (grid[y][x] != '0' && grid[y][x] != ' ')
		return ;
	grid[y][x] = 'V';
	flood_fill(data, grid, x + 1, y, max_x, max_y);
	flood_fill(data, grid, x - 1, y, max_x, max_y);
	flood_fill(data, grid, x, y + 1, max_x, max_y);
	flood_fill(data, grid, x, y - 1, max_x, max_y);
}

bool	has_unclosed_spaces(char **grid)
{
	int	y;
	int	x;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == '0' || grid[y][x] == ' ')
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}
