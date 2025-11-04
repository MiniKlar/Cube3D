#include "../parsing.h"

char	*get_and_clean_line(t_data *data, int fd, char **line_ptr)
{
	char	*trimmed_line;

	*line_ptr = get_next_line(fd);
	if (!*line_ptr)
		ft_error_exit(data, "Incomplete file.");
	if (ft_is_empty_line(*line_ptr))
		return (free(*line_ptr), NULL);
	trimmed_line = ft_strtrim_start(*line_ptr);
	return (trimmed_line);
}

bool	extract_and_validate_value(t_data *data, char *trimmed, int *count)
{
	char	*value;
	bool	success;

	success = false;
	if (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3)
		|| !ft_strncmp(trimmed, "WE ", 3) || !ft_strncmp(trimmed, "EA ", 3))
		value = trimmed + 3;
	else if (!ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2))
		value = trimmed + 2;
	else
		ft_error_exit(data, "missing configuration identifier.");
	value = ft_strtrim(value, " \t\n");
	if (ft_strlen(value) == 0)
		ft_error_exit(data, "Missing texture path.");
	if (!ft_strncmp(trimmed, "NO ", 3) || !ft_strncmp(trimmed, "SO ", 3)
		|| !ft_strncmp(trimmed, "EA ", 3) || !ft_strncmp(trimmed, "WE ", 3))
		success = validate_texture(data, value, trimmed[0]);
	else if (!ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2))
		success = validate_color(data, value, trimmed[0]);
	if (success)
		(*count)++;
	else
		ft_error_exit(data, "Wrong format or missing value.");
	return (true);
}

char	*find_first_map_line(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && ft_is_empty_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		ft_error_exit(data, "The map is missing after the configuration.");
	return (line);
}

char	*parse_config(t_data *data, int fd)
{
	char	*line;
	char	*trimmed_line;
	int		found_count;

	found_count = 0;
	while (found_count < CONFIG_COUNT)
	{
		trimmed_line = get_and_clean_line(data, fd, &line);
		if (trimmed_line == NULL)
			continue ;
		extract_and_validate_value(data, trimmed_line, &found_count);
		free(line);
	}
	return (find_first_map_line(data, fd));
}
