/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:06:05 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/12 12:05:51 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include "minilibx_macos/mlx.h"
# define width 1920
# define height 1080
# define rect_width 200
# define rect_height 200
# define W 13
# define A 0
# define S 1
# define D 2

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img; // image identifier
	char	*addr; // address of the first byte of the image
	int		bits_per_pixel; // number of bits needed to represent a pixel color
	int		line_length; // size of a line in bytes
	int		endian; // useless on macos, client and graphical framework have the same endian
	int		x_img;
	int		y_img;
	int		color;
}				t_data;

int	closeclose(t_data *data)
{
	if (data->mlx)
		mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x > 0 && y > 0 && x < width && y < height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_rect_filled(t_data *img, int x_start, int y_start, int width_rect, int height_rect, int color)
{
	int	x;
	int	y;
	int	colorPrint;

	x = 0;
	colorPrint = color;
	while (x < width_rect)
	{
		y = 0;
		while (y < height_rect)
		{
			if (color == 1)
				colorPrint = rand() % 0xFFFFFF;
			my_mlx_pixel_put(img, x_start + x, y_start + y, colorPrint);
			y++;
		}
		x++;
	}
}

void	draw_rect (t_data *img, int x_start, int y_start, int width_rect, int height_rect, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < width_rect)
	{
		y = 0;
		while (y < height_rect)
		{
			if (x == 0 || x == width_rect - 1 || y == 0 || y == height_rect - 1)
				my_mlx_pixel_put(img, x_start + x, y_start + y, color);
			y++;
		}
		x++;
	}
}

int	render_next_frame(t_data *img)
{
	mlx_destroy_image(img->mlx, img->img); // clear the window
	img->img = mlx_new_image(img->mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	draw_rect_filled(img, img->x_img, img->y_img, rect_width, rect_height, img->color); // prints a red rectangle with a width of 200 and a height of 200 at coordinates (1000, 500)
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0); // print the image in the window
	return (0);
}

int	key_hook(int keycode, t_data *img)
{
	if (keycode == W && img->y_img > 0) // Move the rectangle up
		img->y_img -= 20;
	if (keycode == A && img->x_img > 0) // Move the rectangle to the left
		img->x_img -= 20;
	if (keycode == S && img->y_img < height - rect_height) // Move the rectangle down
		img->y_img += 20;
	if (keycode == D && img->x_img < width - rect_width) // Move the rectangle to the right
		img->x_img += 20;
	if (keycode == 53) // Press ESC
		closeclose(img);
	if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2) // only render if WASD was pressed
		render_next_frame(img);
	return (0);
}

int	main(void)
{
	t_data	img;

	img.color = 1; // set the color of the rectanle
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, width, height, "DAS SUPER FENSTER"); // create a new window
	img.img = mlx_new_image(img.mlx, width, height); // create a new image
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);// get the address of the first byte of the image
	img.x_img = 960; // set x and y value to the mid of the screen
	img.y_img = 440;

	draw_rect_filled (&img, img.x_img, img.y_img, rect_width, rect_height, img.color); // prints a red rectangle with a width of 200 and a height of 200 at coordinates (1000, 500)
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0); // print the image in the window

	mlx_hook(img.mlx_win, 2, 1L<<0, key_hook, &img); // call the key_hook function when a key is pressed
	mlx_hook(img.mlx_win, 17, 1L<<17, closeclose, &img); // call the close function when the red x is clicked
	mlx_loop(img.mlx); // wait for events
}

