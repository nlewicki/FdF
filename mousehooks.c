/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:47:49 by nlewicki          #+#    #+#             */
/*   Updated: 2024/06/11 13:10:52 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include <stdlib.h>
#include <stdio.h>

# define width 640
# define height 480

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	int		x;
	int		y;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	printf("%i\n", keycode);
	return (0);
}
int	mouse_pos(int button, int x, int y, t_vars *vars)
{
	vars->x = x;
	vars->y = y;
	printf("Button: %i, x: %i, y: %i\n", button, x, y);
	return (0);
}

int	mouse_move(int x, int y, t_vars *vars)
{
	if (x > 0 && y > 0 && x < 640 && y < 480)
		printf("x: %i, y: %i\n", x, y);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, width, height, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_pos, &vars);
	mlx_hook(vars.win, 6, 1L<<6, mouse_move, &vars);
	mlx_loop(vars.mlx);
}
