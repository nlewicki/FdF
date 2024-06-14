/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:32:26 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/14 12:12:27 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	set_middle(t_data *data, int x0_or_x1)
{
	int	x;
	int	y;

	x = (width / 2) + data->move_x;
	y = (height / 2) - (data->point.y / 2) * data->zoom + data->move_y;
	if (x0_or_x1 == 0)
	{
		data->xs.x0 += x;
		data->xs.y0 += y;
	}
	else
	{
		data->xs.x1 += x;
		data->xs.y1 += y;
	}
}

void	decide_color(t_data *data, int x, int y, int r_or_b)
{
	data->fade = 0xFFA500;

	if (r_or_b == 0)
	{
		if (data->point.z[y][x] * data->incr_z  == 0 && data->point.z[y][x + 1] * data->incr_z == 0)
			data->color = 0xFFFFFF;
		else if (data->point.z[y][x] * data->incr_z  > 0 && data->point.z[y][x + 1] * data->incr_z > 0)
			data->color = 0xe600e6;
		else if (data->point.z[y][x] * data->incr_z  < 0 && data->point.z[y][x + 1] * data->incr_z < 0)
			data->color = 0x0000FF;
		else
			data->color = 0x660066;
	}
	else
	{
		if (data->point.z[y][x] * data->incr_z  == 0 && data->point.z[y + 1][x] * data->incr_z == 0)
			data->color = 0xFFFFFF;
		else if (data->point.z[y][x] * data->incr_z  > 0 && data->point.z[y + 1][x] * data->incr_z > 0)
			data->color = 0xe600e6;
		else if (data->point.z[y][x] * data->incr_z < 0 && data->point.z[y + 1][x] * data->incr_z < 0)
			data->color = 0x0000FF;
		else
			data->color = 0x660066;
	}
}

void	draw_map(t_data *data)
{
	int		x;
	int		y;

	data->color = 0xFFFFFF;
	y = 0;
	// write(1, "0\n", 2);
	while (y < data->point.y)
	{
		x = 0;
		while (x < data->point.x)
		{
			data->xs.x0 = (x * data->zoom);
			data->xs.y0 = (y * data->zoom);
			to_isometric(&data->xs.x0, &data->xs.y0, data->point.z[y][x] * data->incr_z, data);
			set_middle(data, 0);
			if (x < data->point.x - 1)
			{
				// write(1, "5\n", 2);
				data->xs.x1 = ((x + 1) * data->zoom);
				data->xs.y1 = (y * data->zoom);
				to_isometric(&data->xs.x1, &data->xs.y1, data->point.z[y][x + 1] * data->incr_z, data);
				set_middle(data, 1);
				decide_color(data, x, y, 0);
				dda_algorithm(data);
			}
			if (y  < data->point.y - 1)
			{
				// write(1, "1\n", 2);
				data->xs.x1 = (x * data->zoom);
				data->xs.y1 = ((y + 1) * data->zoom);
				to_isometric(&data->xs.x1, &data->xs.y1, data->point.z[y + 1][x] * data->incr_z, data);
				set_middle(data, 1);
				decide_color(data, x, y, 1);
				dda_algorithm(data);
			}
			x++;
		}
		y++;
	}
}
