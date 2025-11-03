#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/mlx42.h"
#include "../LIB_C/LIB_C.h"

# define WIN_WIDTH  1920
# define WIN_HEIGHT 1080

typedef struct s_textures
{
	// Chemins Textures
	char        *north_path;
	char        *south_path;
	char        *east_path;
	char        *west_path;

	// Textures en elle meme
	xpm_t		*north_tex_file;
	xpm_t		*south_tex_file;
	xpm_t		*east_tex_file;
	xpm_t		*west_tex_file;
	
	uint32_t	floor_color;
	uint32_t	ceiling_color;

} t_textures;

typedef struct s_player
{
	double		pos_x;				// Position X du joueur
	double		pos_y;				// Position Y du joueur
	double		speed;				// Vitesse du joueur
	char		start_direction;	// 'N'/ 'S'/ 'E'/ 'W'
} t_player;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	char		**map;				// La carte parsée
	int			map_width;			// Largeur de la carte
	int			map_height;			// Hauteur de la carte

	t_textures	textures;			// Toutes les données des textures et couleurs
	t_player	player;				// Toutes les données du joueur

} t_data;

// parsing.c
bool	cub_extension(char *file);
bool	parsing(int ac, char **av);

#endif
