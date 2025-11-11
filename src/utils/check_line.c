/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:42:54 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/11 16:02:10 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	is_line_empty(char *line)
{
	while (*line && *line != '\n')
	{
		if (!ft_isspace(*line))
			return (false);
		line++;
	}
	return (true);
}

char	*strtrim_start(char *s)
{
	while (*s != '\0' && ft_isspace(*s))
		s++;
	return (s);
}

size_t	array_len(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
