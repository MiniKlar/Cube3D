/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:25:00 by lomont            #+#    #+#             */
/*   Updated: 2025/11/03 04:23:32 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "MLX42/mlx42.h"

int	main(void)
{
	mlx_t *game;
	printf("Salut\n");
	game = mlx_init(1920, 1080, "Cube3D", true);
	if (!game)
		return (1);
	mlx_image_t* img = mlx_new_image(game, 256, 256);
	if (!img || (mlx_image_to_window(game, img, 0, 0) < 0))
		return (2);

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	mlx_loop(game);
	mlx_terminate(game);
	return (0);
}
