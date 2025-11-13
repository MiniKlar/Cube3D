/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:32:12 by lomont            #+#    #+#             */
/*   Updated: 2025/11/13 11:43:28 by lomont           ###   ########.fr       */
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

void	error_exit(t_app *app, char *msg)
{
	empty_gnl(app);
	printf("Error : %s\n", msg);
	free_app(app);
	exit(EXIT_FAILURE);
}
