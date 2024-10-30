/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:52:06 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/30 09:30:58 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FdF.h"

void	set_middle(t_data *data, int x0_or_x1)
{
	int	x_offset;
	int	y_offset;
	int	total_map_height;
	int	total_map_width;

	total_map_width = data->point.x * data->zoom;
	total_map_height = data->point.y * data->zoom;
	x_offset = (WIDTH / 2) - (total_map_width / 2) + data->move_x;
	y_offset = (HEIGHT / 2) - (total_map_height / 2) + data->move_y;
	if (x0_or_x1 == 0)
	{
		data->xs.x0 += x_offset;
		data->xs.y0 += y_offset;
	}
	else
	{
		data->xs.x1 += x_offset;
		data->xs.y1 += y_offset;
	}
}

void	set_values(t_data *img)
{
	img->move_x = 0;
	img->move_y = 0;
	img->zoom = 5;
	img->incr_z = 1;
	img->persp = 1;
	img->rotate = 0.0;
	img->color = 0xFFFFFF;
	img->rgb.positive = 0xe600e6;
	img->rgb.negative = 0x0000FF;
	img->rgb.base = 0xFFFFFF;
	img->rgb.connection = 0x660066;
}

int	closeclose(t_data *data)
{
	if (data->mlx)
		mlx_destroy_window(data->mlx, data->mlx_win);
	free_data(data);
	exit(0);
}

void	invert_colors(t_data *img)
{
	static int	i = 0;

	if (i == 0)
	{
		img->rgb.positive = 0x0000FF;
		img->rgb.negative = 0xe600e6;
		img->rgb.connection = 0x252850;
		img->rgb.base = 0x888888;
		i = 1;
	}
	else if (i == 1)
	{
		img->rgb.positive = 0xe600e6;
		img->rgb.negative = 0x0000FF;
		img->rgb.connection = 0x660066;
		img->rgb.base = 0xFFFFFF;
		i = 0;
	}
}
