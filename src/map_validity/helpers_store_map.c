/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_store_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:20 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/10 18:43:47 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	get_max_width(char **grid)
{
	int	max_width;
	int	current_len;
	int	i;

	max_width = 0;
	i = 0;
	while (grid[i])
	{
		current_len = ft_strlen(grid[i]);
		if (current_len > max_width)
			max_width = current_len;
		i++;
	}
	return (max_width);
}

char	*pad_line(char *line, int target_width)
{
	char	*new_line;
	int		current_len;
	int		i;

	current_len = ft_strlen(line);
	new_line = ft_calloc(target_width + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < current_len)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		new_line[i] = ' ';
		i++;
	}
	return (new_line);
}

void	rectangularize_and_store(t_data *data, char **temp_grid, int rows)
{
	int		y;
	char	*padded_line;

	data->map_height = rows;
	data->map_width = get_max_width(temp_grid);
	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map)
		error_exit(data, "Final map allocation failed.");
	y = 0;
	while (y < data->map_height)
	{
		padded_line = pad_line(temp_grid[y], data->map_width);
		if (!padded_line)
			error_exit(data, "Map line padding failed.");
		data->map[y] = padded_line;
		y++;
	}
}

void	store_and_clean_map(t_data *data, char **temp_grid, int rows)
{
	data->map_height = rows;
	data->map_width = get_max_width(temp_grid);
	data->map = temp_grid;
}
