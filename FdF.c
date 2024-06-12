/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:02:50 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/12 14:07:37 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	if (x > 0 && y > 0 && x < width && y < height)
	{
		dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
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

int	closeclose(t_data *data)
{
	if (data->mlx)
		mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}

int	render_next_frame(t_data *img)
{
	draw_rect(img, img->x_img, img->y_img, rect_width, rect_height, img->color); // prints a red rectangle with a width of 200 and a height of 200 at coordinates (1000, 500)
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

int	main(int argc, char *argv[])
{
	t_data	img;
	char	*line;
	char	**split;
	int		fd;
	size_t i;

	if (argc != 2)
	{
		printf("Usage: ./fdf [map]\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror("Error");
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, width, height, "SUPER WINDOW");
	img.img = mlx_new_image(img.mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.x_img = 300;
	img.y_img = 300;

	while ((line = get_next_line(fd)))
	{
		ft_printf("%s\n", line);
		split = ft_split(line, ' ');
		i = 0;
		while (split[i] != NULL)
		{
			if (ft_atoi(split[i]) < 0)
			{
				// printf("%i\n", ft_atoi(split[i]));
				img.color = 0x0099FFFF;
				render_next_frame(&img);
				img.x_img += rect_width;
			}
			else if (ft_atoi(split[i]) >= 1)
			{
				// printf("%i\n", ft_atoi(split[i]));
				img.color = 0x00CC33CC;
				render_next_frame(&img);
				img.x_img += rect_width;
			}
			else
			{
				// printf("%i\n", ft_atoi(split[i]));
				img.color = 0x00CCCCCC;
				render_next_frame(&img);
				img.x_img += rect_width;
			}
			i++;
		}
		img.y_img += rect_height;
		img.x_img = 300;
		free(split);
	}
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0); // print the image in the window

	mlx_hook(img.mlx_win, 2, 1L<<0, key_hook, &img); // call the key_hook function when a key is pressed
	mlx_hook(img.mlx_win, 17, 1L<<17, closeclose, &img); // call the close function when the red x is clicked
	mlx_loop(img.mlx); // wait for events
	close(fd);
}
