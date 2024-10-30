/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:09:10 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/30 09:30:46 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FdF.h"

void	malloc_error(t_data *data)
{
	ft_printf("Error: Malloc error\n");
	free_data(data);
	exit(EXIT_FAILURE);
}

void	malloc_z_color(t_data *data, t_read *read)
{
	data->point.z[read->i] = malloc(sizeof(int) * data->point.x);
	data->point.color[read->i] = malloc(sizeof(char *) * data->point.x);
	if (data->point.z[read->i] == NULL || data->point.color[read->i] == NULL)
	{
		malloc_error(data);
		close(read->fd);
	}
}

void	malloc_array(t_data *data, t_read *read)
{
	data->point.z = malloc(sizeof(int *) * data->point.y);
	data->point.color = malloc(sizeof(char **) * data->point.y);
	if (data->point.z == NULL || data->point.color == NULL)
	{
		ft_free(data->point.y - 1, read->map_lines);
		malloc_error(data);
	}
}
