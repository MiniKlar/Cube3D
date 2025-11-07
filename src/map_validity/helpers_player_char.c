#include "../parsing.h"

bool	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

void	set_player_pos(t_data *data, char **grid, int x, int y)
{
	data->player.pos_x = (double)x + 0.5;
	data->player.pos_y = (double)y + 0.5;
	data->player.start_direction = grid[y][x];
	grid[y][x] = '0';
}
