#include "header.h"

int	main(int ac, char **av)
{
	// t_data data;
	mlx_t *game;
	
	printf("Salut\n");
	if (ac == 2)
	{
		if (!parsing(ac, av))
		{
			game = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cube3D", true);
			if (!game)
				return (1);
			mlx_image_t* img = mlx_new_image(game, 256, 256);
			if (!img || (mlx_image_to_window(game, img, 0, 0) < 0))
				return (2);
		
			// Even after the image is being displayed, we can still modify the buffer.
			mlx_put_pixel(img, 0, 0, 0xFF0000FF);
		
			mlx_loop(game);
			mlx_terminate(game);
		}
	}
	else
		return (ft_printf("Error : Usage : ./Cube3d <map.cub>\n"), 1);
	return (0);
}
