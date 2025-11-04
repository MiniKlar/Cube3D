#include "parsing.h"

bool	cub_extension(char *file)
{
	int	len;

	if (!file)
		return (0);
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	if (ft_strncmp(file + (len - 4), ".cub", 4) == 0)
		return (1);
	return (0);
}

int	readable_map(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error : ");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

bool	parsing(t_data *data, char *file)
{
	int		fd;
	char	*first_map_line;

	if (!cub_extension(file))
		ft_error_exit(data, "File must end with <.cub>\n");
	fd = readable_map(file);
	first_map_line = parse_config(data, fd);
	if (!first_map_line)
		ft_error_exit(data, "Map not found after configuration\n");
	close(fd);
	return (printf("End of Parsing\n"), 0);
}
