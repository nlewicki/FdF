/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:50:01 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/14 11:57:42 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	read_map(char *file, t_data *data)
{
	t_read	read;

	read.i = 0;
	read.fd = open(file, O_RDONLY);
	read.line = get_next_line(read.fd);
	while (read.line)
	{
		data->point.y++;
		ft_printf("%s\n", read.line);
		free(read.line);
		read.line = get_next_line(read.fd);
	}
	close(read.fd);
	data->point.z = malloc(sizeof(int *) * data->point.y);
	read.fd = open(file, O_RDONLY);
	read.line = get_next_line(read.fd);
	read.split = ft_split(read.line, ' ');
	while (read.split[read.i])
	{
		data->point.x++;
		read.i++;
	}
	printf("x = %d, y = %d\n", data->point.x, data->point.y);
	close(read.fd);
	read_z(data, file);
}

void	read_z(t_data *data, char *file)
{
	t_read	read;

	read.i = 0;
	read.fd = open(file, O_RDONLY);
	read.line = get_next_line(read.fd);
	while (read.line)
	{
		read.split = ft_split(read.line, ' ');
		data->point.z[read.i] = malloc(sizeof(int) * data->point.x);
		read.j = 0;
		while (read.split[read.j])
		{
			data->point.z[read.i][read.j] = ft_atoi(read.split[read.j]);
			if ((data->point.z[read.i][read.j] / 10) < 1)
				ft_printf("%d  ", data->point.z[read.i][read.j]);
			else
				ft_printf("%d ", data->point.z[read.i][read.j]);
			read.j++;
		}
		free(read.line);
		read.line = get_next_line(read.fd);
		read.i++;
		ft_printf("\n");
	}
	close(read.fd);
}
