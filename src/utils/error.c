/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:32:12 by lomont            #+#    #+#             */
/*   Updated: 2025/11/13 00:59:24 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	error_exit_1(t_app *app, char *msg, char **tab)
{
	free_tab(tab);
	error_exit(app, msg, -1);
}

void	error_exit_2(t_app *app, char *msg, char **tab, char *tab_2)
{
	free_tab(tab);
	free(tab_2);
	error_exit(app, msg, -1);
}

void	error_exit(t_app *app, char *msg, int fd)
{
	char	*tmp;

	tmp = NULL;
	if (fd != -1)
	{
		tmp = get_next_line(fd);
		while (tmp)
		{
			free(tmp);
			tmp = get_next_line(fd);
		}
		if (tmp)
			free(tmp);
	}
	printf("Error : %s\n", msg);
	free_app(app);
	exit(EXIT_FAILURE);
}
