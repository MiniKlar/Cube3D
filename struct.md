typedef struct s_struct
{
	t_data		*data;
	mlx_t		*mlx;
	t_init		*init;
	t_C_list	*first_node;
}				t_struct;



typedef struct s_data
{

	int floor_rgb[3];
	int ceilling_rbg[3];

	mlx_image_t		*texture_north;
	mlx_image_t		*texture_south;
	mlx_image_t		*texture_east;
	mlx_image_t		*texture_west;
	mlx_image_t		*texture_gun;

	mlx_texture_t		*texture_north;
	mlx_texture_t		*texture_south;
	mlx_texture_t		*texture_east;
	mlx_texture_t		*texture_west;
	mlx_texture_t		*texture_gun;
}				t_data;


 // Texture mur (4 textures différentes) + Couleur Sol (R, G, B) + Couleur (R, G, B) Plafond + arme
