/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:50:01 by nlewicki          #+#    #+#             */
/*   Updated: 2024/07/05 09:49:33 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	fill_map_lines(t_read *read, t_data *data)
{
	read->map_lines[read->ind] = get_next_line(read->fd);
	if (read->map_lines[read->ind] != NULL)
	{
		read->current_width = get_line_width(read->map_lines[read->ind]);
		check_map(read, data);
		read->ind++;
	}
}

void	fill_z_color(t_data *data, t_read *read)
{
	char	*trimmed;

	trimmed = ft_strtrim(read->split[read->j], " \t\n\r");
	if (trimmed && *trimmed)
	{
		data->point.z[read->i][read->j] = ft_atoi(trimmed);
		read->color_str = ft_strchr(trimmed, ',');
		if (read->color_str)
		{
			read->color_str++;
			data->point.color[read->i][read->j] = ft_strdup(read->color_str);
		}
		else
			data->point.color[read->i][read->j] = NULL;
	}
	else
	{
		data->point.z[read->i][read->j] = 0;
		data->point.color[read->i][read->j] = NULL;
	}
	free(trimmed);
	read->j++;
}

void	get_y(t_data *data, t_read *read, char *file)
{
	char	*line;

	read->fd = open(file, O_RDONLY);
	if (read->fd == -1)
		return ;
	line = get_next_line(read->fd);
	while (line != NULL)
	{
		free(line);
		data->point.y++;
		line = get_next_line(read->fd);
	}
	free(line);
	close(read->fd);
}

void	read_map(char *file, t_data *data)
{
	t_read	read;

	read.expected_width = -1;
	get_y(data, &read, file);
	read.map_lines = malloc(sizeof(char *) * (data->point.y + 1));
	if (read.map_lines == NULL)
		malloc_error(data);
	read.fd = open(file, O_RDONLY);
	if (read.fd == -1)
		return ;
	read.ind = 0;
	while (read.ind < data->point.y)
		fill_map_lines(&read, data);
	read.map_lines[read.ind] = NULL;
	close(read.fd);
	if (data->point.y == 0 || data->point.x == 0)
		map_is_empty(data);
	malloc_array(data, &read);
	read_z(data, read.map_lines);
	ft_free(data->point.y, read.map_lines);
}

void	read_z(t_data *data, char **map_lines)
{
	t_read	read;

	read.i = 0;
	while (map_lines[read.i])
	{
		read.split = ft_split(map_lines[read.i], ' ');
		malloc_z_color(data, &read);
		read.j = 0;
		while (read.j < data->point.x && read.split[read.j])
			fill_z_color(data, &read);
		ft_free(data->point.x, read.split);
		read.i++;
	}
}
