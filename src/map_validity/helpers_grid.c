/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:15 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/11 16:02:10 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	is_map_started(char **grid)
{
	if (!grid)
		return (false);
	if (grid[0] != NULL)
		return (true);
	return (false);
}

char	**realloc_grid(t_app *app, char **old_grid, int new_rows)
{
	char	**new_grid;
	int		i;

	i = 0;
	new_grid = ft_calloc(new_rows + 1, sizeof(char *));
	if (!new_grid)
		error_exit_1(app, "Grid reallocation failed.", old_grid);
	while (old_grid[i] != NULL && i < new_rows)
	{
		new_grid[i] = old_grid[i];
		i++;
	}
	free(old_grid);
	return (new_grid);
}

char	*strtrim_end_nl(char *line)
{
	int	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	while (len > 0)
	{
		if (line[len - 1] == '\n' || line[len - 1] == ' '
			|| line[len - 1] == '\t')
			len--;
		else
			break ;
	}
	return (ft_substr(line, 0, len));
}
