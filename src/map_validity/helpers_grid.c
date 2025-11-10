/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:16:15 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/10 19:10:56 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

bool	is_map_started(char **grid)
{
	if (!grid)
		return (false);
	if (grid[0] != NULL)
		return (true);
	return (false);
}

char	**realloc_grid(t_data *data, char **old_grid, int new_rows)
{
	char	**new_grid;
	int		i;

	i = 0;
	new_grid = ft_calloc(new_rows + 1, sizeof(char *));
	if (!new_grid)
		error_exit_1(data, "Grid reallocation failed.", old_grid);
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
			|| line[len - 1] == '\t' || line[len - 1] == (char)160)
			len--;
		else
			break ;
	}
	return (ft_substr(line, 0, len));
}
