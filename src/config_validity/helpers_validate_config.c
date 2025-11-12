/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_validate_config.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miniklar <miniklar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:26 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/12 21:56:18 by miniklar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

uint32_t	rgb_to_uint(t_app *app, char *rgb_str)
{
	int			r;
	int			g;
	int			b;
	char		**parts;
	uint32_t	color;

	parts = ft_split(rgb_str, ',');
	if (!parts || array_len(parts) != 3)
	{
		free_tab(parts);
		error_exit(app, "Invalid Color Format (R/G/B).", -1);
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_tab(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit(app, "RGB values are not between [0-255].", -1);
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (color);
}

bool	validate_color(t_app *app, char *rgb_str, char *trimmed)
{
	uint32_t	*target;

	target = NULL;
	if (trimmed[0] == 'C')
		target = &app->ceiling;
	else if (trimmed[0] == 'F')
		target = &app->floor;
	if (*target != 0)
	{
		free(trimmed);
		error_exit(app, "Color already defined.", -1);
	}
	*target = rgb_to_uint(app, rgb_str);
	if (*target)
		return (true);
	return (false);
}

void	assign_texture(t_app *app, char *trimmed, char ***target_ptr)
{
	if (trimmed[0] == 'N')
		*target_ptr = &app->tex.north_path;
	else if (trimmed[0] == 'S')
		*target_ptr = &app->tex.south_path;
	else if (trimmed[0] == 'E')
		*target_ptr = &app->tex.east_path;
	else if (trimmed[0] == 'W')
		*target_ptr = &app->tex.west_path;
}

bool	validate_texture(t_app *app, char *path_str, char *trimmed)
{
	int		fd;
	char	**target_ptr;

	target_ptr = NULL;
	assign_texture(app, trimmed, &target_ptr);
	if (*target_ptr != NULL)
	{
		free(path_str);
		free(trimmed);
		error_exit(app, "Identifier already defined.", -1);
	}
	if (!path_str || ft_strlen(path_str) == 0)
		error_exit(app, "Missing texture path.", app->fd);
	fd = open(path_str, O_RDONLY);
	if (fd < 0)
	{
		free(path_str);
		free(trimmed);
		error_exit(app, "Unreadable texture.", -1);
	}
	close(fd);
	*target_ptr = ft_strdup(path_str);
	if (!*target_ptr)
		error_exit(app, "Memory Allocation failled for the path.", -1);
	return (1);
}
