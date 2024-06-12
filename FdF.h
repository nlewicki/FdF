/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:22:45 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/12 14:06:24 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include "minilibx_macos/mlx.h"
# include "lib/get_next_line/get_next_line.h"
# include "lib/libft/libft.h"
# include "lib/ft_printf/ft_printf.h"

# define width 1920
# define height 1080
# define rect_width 25
# define rect_height 25
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
	int		iso_x_img;
	int		iso_y_img;
}				t_data;

#endif
