/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:32:26 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/30 09:30:37 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FdF.h"

void	check_axis(t_data *data, int x, int y, int axis)
{
	if (axis == 0)
	{
		data->c.z_next = data->point.z[y][x + 1] * data->incr_z;
		data->c.color_next = data->point.color[y][x + 1];
	}
	else
	{
		data->c.z_next = data->point.z[y + 1][x] * data->incr_z;
		data->c.color_next = data->point.color[y + 1][x];
	}
}

void	decide_color(t_data *data, int x, int y, int axis)
{
	data->c.z_current = data->point.z[y][x] * data->incr_z;
	data->c.color_current = data->point.color[y][x];
	check_axis(data, x, y, axis);
	if (data->c.z_current == 0 && data->c.z_next == 0)
		color_base(data);
	else if (data->c.z_current > 0 && data->c.z_next > 0)
		color_positives(data);
	else if (data->c.z_current < 0 && data->c.z_next < 0)
		color_negatives(data);
	else
		color_connection(data);
}

void	draw_map_xy(t_data *data, int x, int y, int v)
{
	if (v == 1)
	{
		data->xs.x1 = ((x + 1) * data->zoom);
		data->xs.y1 = (y * data->zoom);
		to_isometric(&data->xs.x1, &data->xs.y1,
			data->point.z[y][x + 1] * data->incr_z, data);
		set_middle(data, 1);
		decide_color(data, x, y, 0);
		dda_algorithm(data);
	}
	else
	{
		data->xs.x1 = (x * data->zoom);
		data->xs.y1 = ((y + 1) * data->zoom);
		to_isometric(&data->xs.x1, &data->xs.y1,
			data->point.z[y + 1][x] * data->incr_z, data);
		set_middle(data, 1);
		decide_color(data, x, y, 1);
		dda_algorithm(data);
	}
}

void	draw_map(t_data *data)
{
	int		x;
	int		y;

	data->color = 0xFFFFFF;
	y = 0;
	while (y < data->point.y)
	{
		x = 0;
		while (x < data->point.x)
		{
			data->xs.x0 = (x * data->zoom);
			data->xs.y0 = (y * data->zoom);
			to_isometric(&data->xs.x0, &data->xs.y0,
				data->point.z[y][x] * data->incr_z, data);
			set_middle(data, 0);
			if (x < data->point.x - 1)
				draw_map_xy(data, x, y, 1);
			if (y < data->point.y - 1)
				draw_map_xy(data, x, y, 0);
			x++;
		}
		y++;
	}
}
