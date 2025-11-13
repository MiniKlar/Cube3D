/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_validate_config.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:26 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/13 16:42:13 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	valid_int(char *part, int *out)
{
	int	value;

	if (!part || *part == '\0')
		return (false);
	if (!is_only_digits(part) || ft_strlen(part) > 3)
		return (false);
	value = ft_atoi(part);
	if (value < 0 || value > 255)
		return (false);
	*out = value;
	return (true);
}

uint32_t	rgb_to_uint(t_app *app, char *rgb_str, char *trimmed)
{
	t_rgb		rgb;
	char		**parts;
	char		*tmp_part;
	int			i;

	parts = ft_split(rgb_str, ',');
	if (!parts || array_len(parts) != 3)
		error_exit_3(app, parts, rgb_str, trimmed);
	i = 0;
	while (parts[i])
	{
		tmp_part = parts[i];
		parts[i] = ft_strtrim(tmp_part, " \t\n");
		free(tmp_part);
		i++;
	}
	if (!(valid_int(parts[0], &rgb.r)) || !(valid_int(parts[1], &rgb.g))
		|| !(valid_int(parts[2], &rgb.b)))
		error_exit_3(app, parts, rgb_str, trimmed);
	free_tab(parts);
	rgb.color = (rgb.r << 24) | (rgb.g << 16) | (rgb.b << 8) | 0xFF;
	return (rgb.color);
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
		error_exit(app, "Color already defined.");
	}
	*target = rgb_to_uint(app, rgb_str, trimmed);
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
		error_exit(app, "Identifier already defined.");
	}
	if (!path_str || ft_strlen(path_str) == 0)
		error_exit(app, "Missing texture path.");
	fd = open(path_str, O_RDONLY);
	if (fd < 0)
	{
		free(path_str);
		free(trimmed);
		error_exit(app, "Unreadable texture.");
	}
	close(fd);
	*target_ptr = ft_strdup(path_str);
	if (!*target_ptr)
		error_exit(app, "Memory Allocation failled for the path.");
	return (1);
}
