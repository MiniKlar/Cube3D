/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:42:58 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/10 18:42:59 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->player.speed = 0.05;
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->textures.north_path)
		free(data->textures.north_path);
	if (data->textures.south_path)
		free(data->textures.south_path);
	if (data->textures.east_path)
		free(data->textures.east_path);
	if (data->textures.west_path)
		free(data->textures.west_path);
	if (data->map)
	{
		while (i < data->map_height)
		{
			if (data->map[i])
				free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}
