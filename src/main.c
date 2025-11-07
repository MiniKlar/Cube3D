#include "parsing.h"

bool	parsing(t_data *data, char *file)
{
	int		fd;
	char	*first_line_map;

	if (!cub_extension(file))
		error_exit(data, "File must end with <.cub>");
	fd = readable_map_file(file);
	first_line_map = parse_config(data, fd);
	if (!first_line_map)
		error_exit(data, "The map is missing after the configuration");
	parse_map(data, fd, first_line_map);
	close(fd);
	return (printf("End of Parsing\n"), 0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 2)
	{
		init_data(&data);
		if (!parsing(&data, av[1]))
		{
			data.game = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cube3D", true);
			if (!data.game)
				return (1);
			mlx_image_t	*img = mlx_new_image(data.game, 256, 256);
			if (!img || (mlx_image_to_window(data.game, img, 0, 0) < 0))
				return (2);
			mlx_put_pixel(img, 0, 0, 0xFF0000FF);
			mlx_loop(data.game);
			mlx_terminate(data.game);
		}
	}
	else
		return (ft_printf("Error : Usage : ./Cube3d <map.cub>\n"), 1);
	return (0);
}
