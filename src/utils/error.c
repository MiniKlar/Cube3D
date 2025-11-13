/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:32:12 by lomont            #+#    #+#             */
/*   Updated: 2025/11/13 16:36:08 by abeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	empty_gnl(t_app *app)
{
	char	*tmp;

	tmp = get_next_line(app->fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(app->fd);
	}
	if (tmp)
		free(tmp);
}

void	error_exit_1(t_app *app, char *msg, char **tab)
{
	empty_gnl(app);
	free_tab(tab);
	error_exit(app, msg);
}

void	error_exit_2(t_app *app, char *msg, char **tab, char *tab_2)
{
	empty_gnl(app);
	free_tab(tab);
	free(tab_2);
	error_exit(app, msg);
}

void	error_exit_3(t_app *app, char **tab, char *tab_2, char *tab_3)
{
	empty_gnl(app);
	free_tab(tab);
	free(tab_2);
	free(tab_3);
	error_exit(app, "Invalid color value");
}

void	error_exit(t_app *app, char *msg)
{
	empty_gnl(app);
	printf("Error : %s\n", msg);
	free_app(app);
	exit(EXIT_FAILURE);
}
