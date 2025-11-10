/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:23 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/10 19:18:05 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	**assemble_grid(t_data *data, int fd, char *first_line, int *rows)
{
	char	**grid;
	char	*line;
	int		i;

	i = 1;
	grid = ft_calloc(2, sizeof(char *));
	if (!grid)
		error_exit(data, "Grid memory fail.");
	grid[0] = first_line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_line_empty(line) && is_map_started(grid))
			error_exit_2(data, "Empty line inside map data.", grid, line);
		if (is_line_empty(line))
		{
			free(line);
			continue ;
		}
		grid = realloc_grid(data, grid, i + 1);
		grid[i] = strtrim_end_nl(line);
		free(line);
		i++;
	}
	*rows = i;
	if (*rows < 3)
		error_exit_2(data, "Map too small or invalid structure.", grid, line);
	return (grid);
}

void	validate_chars_and_player(t_data *data, char **grid, int rows)
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
				error_exit_1(data, "Invalid character in map.", grid);
			if (is_player_char(grid[y][x]))
			{
				set_player_pos(data, grid, x, y);
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
		error_exit_1(data, "Map must contain one player position.", grid);
}

void	check_map_closure(t_data *data)
{
	char	**test_grid;

	test_grid = copy_grid(data);
	if (!test_grid)
		error_exit(data, "Failed to allocate memory for test grid.");
	launch_flood_fill_from_player(data, test_grid);
	free_tab(test_grid);
}

void	parse_map(t_data *data, int fd, char *first_line_map)
{
	char	**temp_grid;
	int		rows;

	temp_grid = assemble_grid(data, fd, first_line_map, &rows);
	validate_chars_and_player(data, temp_grid, rows);
	store_and_clean_map(data, temp_grid, rows);
	check_map_closure(data);
}
