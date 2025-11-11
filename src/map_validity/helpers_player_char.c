/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_player_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:18 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/11 18:49:02 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void	set_player_pos(t_app *app, char **grid, int x, int y)
{
	app->player.pos_x = (double)x + 0.5;
	app->player.pos_y = (double)y + 0.5;
	app->direction = grid[y][x];
	grid[y][x] = '0';
}
