/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:22:45 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/14 12:13:31 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "minilibx_macos/mlx.h"
# include "lib/get_next_line/get_next_line.h"
# include "lib/libft/libft.h"
# include "lib/ft_printf/ft_printf.h"

# define width 1920
# define height 1080
# define W 13
# define A 0
# define S 1
# define D 2

typedef struct	s_xs
{
	int x0;
	int x1;
	int y0;
	int y1;
}				t_xs;

typedef struct	s_line
{
	int		dx;
	int		dy;
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;
	int		steps;
}				t_line;

typedef struct	s_point
{
	int	x;
	int	y;
	int	**z;
}				t_point;

typedef struct	s_read
{
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		j;
}				t_read;

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img; // image identifier
	char	*addr; // address of the first byte of the image
	int		bits_per_pixel; // number of bits needed to represent a pixel color
	int		line_length; // size of a line in bytes
	int		endian; // useless on macos, client and graphical framework have the same endian
	int		color;
	int		fade;
	int		zoom;
	int		move_x;
	int		move_y;
	int		incr_z;
	int		perspective;
	t_point	point;
	t_xs	xs;
}				t_data;

void	dda_algorithm(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y);
void	to_isometric(int *x, int *y, int z, t_data *data);
void	draw_map(t_data *data);
void	read_z(t_data *data, char *file);
void	read_map(char *file, t_data *data);
void	decide_color(t_data *data, int x, int y, int r_or_b);
void	set_middle(t_data *data, int r_or_b);
// void	fade_color(t_data *data, int start_c, int end_c, float t);

#endif
