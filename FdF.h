/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:22:45 by nlewicki          #+#    #+#             */
/*   Updated: 2024/07/03 09:17:46 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "minilibx_macos/mlx.h"
# include "lib/get_next_line/get_next_line.h"
# include "lib/libft/libft.h"
# include "lib/ft_printf/ft_printf.h"

# define WIDTH 1920
# define HEIGHT 1080
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define ESC 53
# define PLUS 24
# define MINUS 27
# define P 35
# define I 34
# define R 15

typedef struct s_decid
{
	int		z_current;
	int		z_next;
	char	*color_current;
	char	*color_next;
}	t_decid;

typedef struct s_rgb
{
	int	positive;
	int	negative;
	int	connection;
	int	base;
}			t_rgb;

typedef struct s_iso
{
	double	prev_x;
	double	prev_y;
	double	iso_x;
	double	iso_y;
	double	rot_x;
	double	rot_y;
}			t_iso;

typedef struct s_xs
{
	int	x0;
	int	x1;
	int	y0;
	int	y1;
}				t_xs;

typedef struct s_line
{
	int		dx;
	int		dy;
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;
	int		steps;
}				t_line;

typedef struct s_point
{
	int		x;
	int		y;
	int		**z;
	char	***color;
}				t_point;

typedef struct s_read
{
	int		fd;
	char	*line;
	char	**split;
	int		i;
	int		j;
	int		expected_width;
	int		line_number;
	int		len;
	int		current_width;
	char	*color_str;
	char	**map_lines;
	int		ind;
}				t_read;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		linelen;
	int		endian;
	int		color;
	int		fade;
	int		zoom;
	double	rotate;
	int		move_x;
	int		move_y;
	int		incr_z;
	int		persp;
	t_decid	c;
	t_rgb	rgb;
	t_point	point;
	t_xs	xs;
}				t_data;

// ------<>------ draw ------<>------
void	decide_color_0(t_data *data, int x, int y);
void	decide_color_1(t_data *data, int x, int y);
void	decide_color(t_data *data, int x, int y, int r_or_b);
void	draw_map_xy(t_data *data, int x, int y, int v);
void	draw_map(t_data *data);

// ------<>------ draw_color ------<>------
void	color_base(t_data *data);
void	color_positives(t_data *data);
void	color_negatives(t_data *data);
void	color_connection(t_data *data);

// ------<>------ FdF ------<>------
int		key_hook2(int keycode, t_data *img);
int		key_hook(int keycode, t_data *img);
void	to_isometric(int *x, int *y, int z, t_data *data);

// ------<>------ read ------<>------
void	fill_z_color(t_data *data, t_read *read);
void	fill_map_lines(t_read *read, t_data *data);
void	read_map(char *file, t_data *data);
void	read_z(t_data *data, char **map_lines);

// ------<>------ read_map_utils ------<>------
int		get_line_width(char *line);
void	map_is_empty(t_data *data);
void	clean_up(t_read *read);
void	map_error(t_read *read);
void	check_map(t_read *read, t_data *data);

// ------<>------ read_map_utils2 ------<>------
void	malloc_error(t_data *data);
void	malloc_array(t_data *data, t_read *read);
void	malloc_z_color(t_data *data, t_read *read);

// ------<>------ utils ------<>------
void	my_mlx_pixel_put(t_data *data, int x, int y);
void	print_background(t_data *data, int color);
void	dda_algorithm(t_data *data);
int		ft_abs(int a);
void	redraw(t_data *img);

// ------<>------ utils2 ------<>------
void	set_middle(t_data *data, int x0_or_x1);
void	set_values(t_data *img);
int		closeclose(t_data *data);
void	invert_colors(t_data *img);

// ------<>------ free ------<>------
void	ft_free(int j, char **result);
void	free_data(t_data *data);
void	free_point(t_data *data);
void	free_color(t_data *data);

#endif
