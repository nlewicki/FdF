/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:02:50 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/30 09:28:54 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FdF.h"

int	key_hook2(int keycode, t_data *img)
{
	if (keycode == UP)
		img->incr_z += 1;
	if (keycode == DOWN)
		img->incr_z -= 1;
	if (keycode == PLUS)
		img->zoom += 5;
	if (keycode == MINUS)
	{
		if (img->zoom > 5)
			img->zoom -= 5;
	}
	if (keycode == P)
	{
		if (img->persp == 1)
			img->persp = 0;
		else
			img->persp = 1;
	}
	return (0);
}

int	key_hook(int keycode, t_data *img)
{
	key_hook2(keycode, img);
	if (keycode == W)
		img->move_y -= 50;
	if (keycode == S)
		img->move_y += 50;
	if (keycode == A)
		img->move_x -= 50;
	if (keycode == D)
		img->move_x += 50;
	if (keycode == R)
		set_values(img);
	if (keycode == I)
		invert_colors(img);
	redraw(img);
	if (keycode == ESC)
		closeclose(img);
	return (0);
}

void	to_isometric(int *x, int *y, int z, t_data *data)
{
	t_iso	iso;

	iso.prev_x = *x - (data->point.x * data->zoom) / 2;
	iso.prev_y = *y - (data->point.y * data->zoom) / 2;
	if (data->persp == 1)
	{
		iso.iso_x = (iso.prev_x - iso.prev_y) * cos(M_PI / 6);
		iso.iso_y = (iso.prev_x + iso.prev_y) * sin(M_PI / 6) - z;
		*x = iso.iso_x + (data->point.x * data->zoom) / 2 + data->move_x;
		*y = iso.iso_y + (data->point.y * data->zoom) / 2 + data->move_y;
	}
	else
	{
		*x = iso.prev_x + (data->point.x * data->zoom) / 2 + data->move_x;
		*y = iso.prev_y + (data->point.y * data->zoom) / 2 + data->move_y;
	}
}

void	set_img(t_data *img)
{
	img->mlx = mlx_init();
	img->mlx_win = mlx_new_window(img->mlx, WIDTH, HEIGHT, "SUPER WINDOW");
	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->linelen, &img->endian);
}

int	main(int argc, char *argv[])
{
	t_data	img;
	t_read	read;

	if (argc != 2)
	{
		ft_printf("Usage: ./fdf [map]\n");
		return (1);
	}
	read.fd = open(argv[1], O_RDONLY);
	if (read.fd == -1)
	{
		ft_printf("Error");
		return (1);
	}
	set_img(&img);
	set_values(&img);
	read_map(argv[1], &img);
	draw_map(&img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 1L << 0, key_hook, &img);
	mlx_hook(img.mlx_win, 17, 1L << 17, closeclose, &img);
	mlx_loop(img.mlx);
	close(read. fd);
	free_data(&img);
	return (0);
}
