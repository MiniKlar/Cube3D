/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_store_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:20 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/11 16:02:10 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void	store_map(t_app *app, char **temp_grid, int rows)
{
	app->map_height = rows;
	app->map_width = get_max_width(temp_grid);
	app->map = temp_grid;
}
