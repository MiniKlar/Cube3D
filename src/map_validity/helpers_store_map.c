/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_store_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:20 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/11 13:26:54 by abeaufil         ###   ########.fr       */
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

void	store_map(t_data *data, char **temp_grid, int rows)
{
	data->map_height = rows;
	data->map_width = get_max_width(temp_grid);
	data->map = temp_grid;
}
