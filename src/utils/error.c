/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:32:12 by lomont            #+#    #+#             */
/*   Updated: 2025/11/11 16:02:10 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	error_exit_1(t_app *app, char *msg, char **tab)
{
	free_tab(tab);
	error_exit(app, msg);
}

void	error_exit_2(t_app *app, char *msg, char **tab, char *tab_2)
{
	free_tab(tab);
	free(tab_2);
	error_exit(app, msg);
}

void	error_exit(t_app *app, char *msg)
{
	printf("Error : %s\n", msg);
	free_app(app);
	exit(EXIT_FAILURE);
}
