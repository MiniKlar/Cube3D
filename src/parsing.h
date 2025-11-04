#ifndef PARSING_H
# define PARSING_H

# include "../MLX42/mlx42.h"
# include "../LIB_C/LIB_C.h"

# define WIN_WIDTH  1080
# define WIN_HEIGHT 920
# define CONFIG_COUNT 6

typedef struct s_textures
{
	char		*north_path;
	char		*south_path;
	char		*east_path;
	char		*west_path;
	xpm_t		*north_tex_file;
	xpm_t		*south_tex_file;
	xpm_t		*east_tex_file;
	xpm_t		*west_tex_file;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
}	t_textures;

typedef struct s_player
{
	double		pos_x;				// Position X du joueur
	double		pos_y;				// Position Y du joueur
	double		speed;				// Vitesse du joueur
	char		start_direction;	// 'N'/ 'S'/ 'E'/ 'W'
}	t_player;

typedef struct s_data
{
	mlx_t		*game;
	mlx_image_t	*img;
	char		**map;				// La carte parsée
	int			map_width;			// Largeur de la carte
	int			map_height;			// Hauteur de la carte
	t_textures	textures;			// Toutes les données des textures
	t_player	player;				// Toutes les données du joueur
}	t_data;

// check_map/
// parse_config.c
bool			ft_is_empty_line(char *line);
char			*ft_strtrim_start(char *s);
size_t			ft_array_len(char **tab);
void			ft_free_tab(char **tab);
// read_map.c
uint32_t		rgb_to_uint(t_data *data, char *rgb_str);
bool			validate_color(t_data *data, char *rgb_str, char c);
bool			validate_texture(t_data *data, char *path_str, char c);
char			*parse_config(t_data *data, int fd);

// utils/
// check_line.c
bool			ft_is_empty_line(char *line);
char			*ft_strtrim_start(char *s);
size_t			ft_array_len(char **tab);
void			ft_free_tab(char **tab);
// error.c
void			ft_error_exit(t_data *data, const char *msg);
// init.c
void			init_data(t_data *data);
void			ft_free_data(t_data *data);

// parsing.c
bool			cub_extension(char *file);
int				readable_map(char *file);
bool			parsing(t_data *data, char *file);

#endif
