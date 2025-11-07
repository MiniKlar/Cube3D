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

// utils/..

bool			is_line_empty(char *line);
char			*strtrim_start(char *s);
size_t			array_len(char **tab);
void			free_tab(char **tab);
void			error_exit(t_data *data, const char *msg);
void			init_data(t_data *data);
void			free_data(t_data *data);

// config_validity/..

uint32_t		rgb_to_uint(t_data *data, char *rgb_str);
bool			validate_color(t_data *data, char *rgb_str, char c);
bool			validate_texture(t_data *data, char *path_str, char c);
char			*get_clean_line(t_data *data, int fd, char **line_ptr);
bool			extract_verif_value(t_data *data, char *trimmed, int *count);
char			*find_first_map_line(t_data *data, int fd);
char			*parse_config(t_data *data, int fd);
bool			cub_extension(char *file);
int				readable_map_file(char *file);

// map_validity/..

char			**copy_grid(t_data *data);
void			launch_flood_fill_from_player(t_data *data, char **grid);
void			flood_fill(t_data *data, char **grid, int x, int y, int max_x, int max_y);
bool			has_unclosed_spaces(char **grid);

bool			is_map_started(char **grid);
char			**realloc_grid(t_data *data, char **old_grid, int new_rows);
char			*strtrim_end_nl(char *line);

bool			is_valid_char(char c);
bool			is_player_char(char c);
void			set_player_pos(t_data *data, char **grid, int x, int y);

char			**assemble_raw_grid(t_data *data, int fd, char *first_line, int *rows);
void			validate_chars_and_player(t_data *data, char **grid, int rows);
void			check_map_closure(t_data *data);

int				get_max_width(char **grid);
char			*pad_line(char *line, int target_width);
void			rectangularize_and_store(t_data *data, char **temp_grid, int rows);
void			store_and_clean_map(t_data *data, char **temp_grid, int rows);

char			**assemble_raw_grid(t_data *data, int fd, char *first_line, int *rows);
void			validate_chars_and_player(t_data *data, char **grid, int rows);
void			check_map_closure(t_data *data);
void			parse_map(t_data *data, int fd, char *first_line_map);

// main

bool			parsing(t_data *data, char *file);

#endif
