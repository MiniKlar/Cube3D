/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:29 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/11 16:01:23 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*get_clean_line(t_app *app, int fd, char **line_ptr)
{
	char	*trimmed_line;

	*line_ptr = get_next_line(fd);
	if (!*line_ptr)
		error_exit(app, "Incomplete file.");
	if (is_line_empty(*line_ptr))
		return (free(*line_ptr), NULL);
	trimmed_line = strtrim_start(*line_ptr);
	return (trimmed_line);
}

int	extract_value(t_app *app, char *trimmed, int *count, bool valid)
{
	char	*value;

	if (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3)
		|| !ft_strncmp(trimmed, "WE ", 3) || !ft_strncmp(trimmed, "EA ", 3))
		value = trimmed + 3;
	else if (!ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2))
		value = trimmed + 2;
	else
		return (1);
	value = ft_strtrim(value, " \t\n");
	if (value == NULL)
		return (2);
	if (ft_strlen(value) == 0)
		return (free(value), 3);
	if (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3)
		|| !ft_strncmp(trimmed, "EA ", 3) || !ft_strncmp(trimmed, "WE ", 3))
		valid = validate_texture(app, value, trimmed);
	else if (!ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2))
		valid = validate_color(app, value, trimmed);
	if (valid)
		(*count)++;
	else
		return (free(value), 4);
	return (free(value), 0);
}

char	*find_first_map_line(t_app *app, int fd)
{
	char	*line;
	char	*cleaned_line;

	line = get_next_line(fd);
	while (line && is_line_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		error_exit(app, "The map is missing after the configuration.");
	cleaned_line = strtrim_end_nl(line);
	free(line);
	return (cleaned_line);
}

void	correct_error(t_app *app, int error, char *trimmed, char *line)
{
	if (error == 1)
	{
		free(line);
		error_exit(app, "missing configuration identifier.");
	}
	else if (error == 2)
		error_exit(app, "Missing texture path.");
	else if (error == 3)
	{
		free(line);
		error_exit(app, "Missing texture path.");
	}
	else if (error == 4)
	{
		free(line);
		error_exit(app, "Wrong format or missing value.");
	}
	(void)trimmed;
}

char	*parse_config(t_app *app, int fd)
{
	char	*line;
	char	*trimmed_line;
	int		found_count;
	bool	success;
	int		verif;

	verif = 0;
	found_count = 0;
	success = false;
	while (found_count < CONFIG_COUNT)
	{
		trimmed_line = get_clean_line(app, fd, &line);
		if (trimmed_line == NULL)
			continue ;
		verif = extract_value(app, trimmed_line, &found_count, success);
		if (verif != 0)
			correct_error(app, verif, trimmed_line, line);
		free(line);
	}
	return (find_first_map_line(app, fd));
}
