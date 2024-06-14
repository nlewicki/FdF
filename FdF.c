/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:02:50 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/14 11:52:59 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y)
{
	char	*dst;

	if (x >= 0 && y > 0 && x < width && y < height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = data->color;
	}
}

void	print_background(t_data *data)
{
	write(1, "print_background\n", 17);
	int i;
	int j;
	i = 0;
	data->color = 0x000000;

	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			my_mlx_pixel_put(data, j, i);
			j++;
		}
		i++;
	}
	write(1, "print_test\n", 10);
}

int	closeclose(t_data *data)
{
	if (data->mlx)
		mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}

int	render_next_frame(t_data *img)
{

	// draw_rect(img, img->x_img, img->y_img, rect_width, rect_height, img->color); // prints a red rectangle with a width of 200 and a height of 200 at coordinates (1000, 500)
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0); // print the image in the window
	return (0);
}

void	redraw(t_data *img)
{
	printf("zoom = %d\n", img->zoom);
	mlx_destroy_image(img->mlx, img->img); // clear the window
	img->img = mlx_new_image(img->mlx, width, height);
	if (!img->img)
		ft_printf("img is NULL\n");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	if (!img->addr)
		ft_printf("addr is NULL\n");
	draw_map(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0); // print the image in the window
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == 126) // up
	{
		img->incr_z += 5;
		redraw(img);
	}
	if (keycode == 125) // down
	{
		img->incr_z -= 5;
		redraw(img);
	}
	if (keycode == 24) // +
	{
		img->zoom += 5;
		redraw(img);
	}
	if (keycode == 27) // -
	{
		if (img->zoom > 5)
			img->zoom -= 5;
		redraw(img);
	}
	if (keycode == 35) // P
	{
		if (img->perspective == 1)
			img->perspective = 0;
		else
			img->perspective = 1;
		redraw(img);
	}
	if (keycode == 13) // W
	{
		write(1, "W\n", 2);
		img->move_y -= 100;
		redraw(img);
	}
	if (keycode == 1) // S
	{
		img->move_y += 100;
		redraw(img);
	}
	if (keycode == 0) // A
	{
		img->move_x -= 100;
		redraw(img);
	}
	if (keycode == 2) // D
	{
		img->move_x += 100;
		redraw(img);
	}
	if (keycode == 53) // ESC
		closeclose(img);
	// if (keycode == 123)
	// {
	// 	img->rotation_angle -= 0.1;
	// 	redraw(img);
	// }
	// if (keycode == 124)
	// {
	// 	img->rotation_angle += 0.1;
	// 	redraw(img);
	// }
	return (0);
}

void dda_algorithm(t_data *data)
{
	t_line	line;
	int		i;

	i = 0;
	line.dy = data->xs.y1 - data->xs.y0;
	line.dx = data->xs.x1 - data->xs.x0;
	if (abs(line.dx) > abs(line.dy))
		line.steps = abs(line.dx);
	else
		line.steps = abs(line.dy);
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

void	to_isometric(int *x, int *y, int z, t_data *data)
{
	if (data->perspective == 1)
	{
		int previous_x = *x;
		int previous_y = *y;
		*x = (previous_x - previous_y) * cos(0.523599);
		*y = (previous_x + previous_y) * sin(0.523599) - z;
	}
	else
		*x -= (data->point.x * data->zoom) / 2;
}

int	main(int argc, char *argv[])
{
	t_data	img;
	char	*line;
	char	**split;
	int		fd;

	if (argc != 2)
	{
		printf("Usage: ./fdf [map]\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror("Error");
	printf("%s\n", argv[1]);
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, width, height, "SUPER WINDOW");
	img.img = mlx_new_image(img.mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	img.move_x = 0;
	img.move_y = 0;
	img.zoom = 5;
	img.incr_z = 1;
	img.perspective = 1;
	write(1, "read\n", 5);
	read_map(argv[1], &img);
	print_background(&img);
	draw_map(&img);

	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0); // print the image in the window
	mlx_hook(img.mlx_win, 2, 1L<<0, key_hook, &img); // call the key_hook function when a key is pressed
	mlx_hook(img.mlx_win, 17, 1L<<17, closeclose, &img); // call the close function when the red x is clicked
	mlx_loop(img.mlx); // wait for events
	close(fd);
	return (0);
}
