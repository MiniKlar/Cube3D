#include "../parsing.h"

uint32_t	rgb_to_uint(t_data *data, char *rgb_str)
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
		error_exit(data, "Invalid Color Format (R/G/B).");
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_tab(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit(data, "RGB values are not between [0-255].");
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (color);
}

bool	validate_color(t_data *data, char *rgb_str, char c)
{
	uint32_t	*target;

	target = NULL;
	if (c == 'C')
		target = &data->textures.ceiling_color;
	else if (c == 'F')
		target = &data->textures.floor_color;
	if (*target != 0)
		error_exit(data, "Color already defined.");
	*target = rgb_to_uint(data, rgb_str);
	if (*target)
		return (true);
	return (false);
}

bool	validate_texture(t_data *data, char *path_str, char c)
{
	int		fd;
	char	**target_ptr;

	target_ptr = NULL;
	if (c == 'N')
		target_ptr = &data->textures.north_path;
	else if (c == 'S')
		target_ptr = &data->textures.south_path;
	else if (c == 'E')
		target_ptr = &data->textures.east_path;
	else if (c == 'W')
		target_ptr = &data->textures.west_path;
	if (*target_ptr != NULL)
		error_exit(data, "Texture already defined.");
	if (!path_str || ft_strlen(path_str) == 0)
		error_exit(data, "Missing texture path.");
	fd = open(path_str, O_RDONLY);
	if (fd < 0)
		error_exit(data, "Unreadable texture.");
	close(fd);
	*target_ptr = ft_strdup(path_str);
	if (!*target_ptr)
		error_exit(data, "Memory Allocation failled for the path.");
	return (true);
}
