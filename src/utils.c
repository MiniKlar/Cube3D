/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomont <lomont@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:32:47 by lomont            #+#    #+#             */
/*   Updated: 2025/11/11 15:32:52 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../parsing.h"

void	error_exit_1(t_data *data, char *msg, char **tab)
{
	free_tab(tab);
	error_exit(data, msg);
}

void	error_exit_2(t_data *data, char *msg, char **tab, char *tab_2)
{
	free_tab(tab);
	free(tab_2);
	error_exit(data, msg);
}

void	error_exit(t_data *data, char *msg)
{
	printf("Error : %s\n", msg);
	free_data(data);
	exit(EXIT_FAILURE);
}
