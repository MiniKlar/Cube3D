/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:23 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/13 17:40:48 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	**assemble_grid(t_app *app, int fd, char *first_line, int *rows)
{
	char	**grid;
	char	*line;
	int		i;

	i = 1;
	grid = ft_calloc(2, sizeof(char *));
	if (!grid)
		error_exit(app, "Grid memory fail.");
	grid[0] = first_line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_line_empty(line) && is_map_started(grid))
			error_exit_2(app, "Empty line inside map.", grid, line);
		grid = realloc_grid(app, grid, i + 1);
		grid[i] = strtrim_end_nl(line);
		free(line);
		i++;
	}
	*rows = i;
	if (*rows < 3)
		error_exit_2(app, "Map too small or invalid structure.", grid, line);
	return (grid);
}

void	validate_chars_and_player(t_app *app, char **grid, int rows)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (grid[y][x])
		{
			if (!is_valid_char(grid[y][x]))
				error_exit_1(app, "Invalid character in map.", grid);
			if (is_player_char(grid[y][x]))
			{
				set_player_pos(app, grid, x, y);
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		error_exit_1(app, "Map must contain one player position.", grid);
}

void	check_map_closure(t_app *app)
{
	char	**test_grid;

	test_grid = copy_grid(app);
	if (!test_grid)
		error_exit(app, "Failed to allocate memory for test grid.");
	launch_flood_fill_from_player(app, test_grid);
	free_tab(test_grid);
}

void	parse_map(t_app *app, int fd, char *first_line_map)
{
	char	**temp_grid;
	int		rows;

	temp_grid = assemble_grid(app, fd, first_line_map, &rows);
	validate_chars_and_player(app, temp_grid, rows);
	store_map(app, temp_grid, rows);
	check_map_closure(app);
}
