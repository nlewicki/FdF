/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:56:45 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/30 09:30:56 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FdF.h"

void	my_mlx_pixel_put(t_data *data, int x, int y)
{
	char	*dst;

	if (x >= 0 && y > 0 && x < WIDTH && y < HEIGHT)
	{
		dst = data->addr
			+ (y * data->linelen + x * (data->bpp / 8));
		*(unsigned int *)dst = data->color;
	}
}

void	print_background(t_data *data, int color)
{
	int	i;
	int	j;

	i = 0;
	data->color = color;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			my_mlx_pixel_put(data, j, i);
			j++;
		}
		i++;
	}
}

void	dda_algorithm(t_data *data)
{
	t_line	line;
	int		i;

	i = 0;
	line.dy = data->xs.y1 - data->xs.y0;
	line.dx = data->xs.x1 - data->xs.x0;
	if (ft_abs(line.dx) > ft_abs(line.dy))
		line.steps = ft_abs(line.dx);
	else
		line.steps = ft_abs(line.dy);
	line.x_inc = (float)line.dx / line.steps;
	line.y_inc = (float)line.dy / line.steps;
	line.x = (float)data->xs.x0;
	line.y = (float)data->xs.y0;
	while (i <= line.steps)
	{
		my_mlx_pixel_put(data, (int)round(line.x), (int)round(line.y));
		line.x += line.x_inc;
		line.y += line.y_inc;
		i++;
	}
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	redraw(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	if (!img->img)
		ft_printf("img is NULL\n");
	img->addr = mlx_get_data_addr(img->img,
			&img->bpp, &img->linelen, &img->endian);
	if (!img->addr)
		ft_printf("addr is NULL\n");
	draw_map(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}
