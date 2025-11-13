/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:42:54 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/13 16:42:21 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_only_digits(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

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
