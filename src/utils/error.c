/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:src/utils.c
/*   utils.c                                            :+:      :+:    :+:   */
========
/*   error.c                                            :+:      :+:    :+:   */
>>>>>>>> origin/parsing:src/utils/error.c
/*                                                    +:+ +:+         +:+     */
/*   By: abeaufil <abeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:src/utils.c
/*   Created: 2025/11/08 02:10:04 by lomont            #+#    #+#             */
/*   Updated: 2025/11/09 01:12:24 by lomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

u_int32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
========
/*   Created: 2025/11/10 18:42:56 by abeaufil          #+#    #+#             */
/*   Updated: 2025/11/10 19:16:42 by abeaufil         ###   ########.fr       */
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
>>>>>>>> origin/parsing:src/utils/error.c
}
