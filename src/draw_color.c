/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:02:51 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/30 09:30:33 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FdF.h"

void	color_base(t_data *data)
{
	if (data->c.color_current != NULL)
		data->color = ft_atoi_base(data->c.color_current, 16);
	else
		data->color = data->rgb.base;
}

void	color_positives(t_data *data)
{
	if (data->c.color_current != NULL)
		data->color = ft_atoi_base(data->c.color_current, 16);
	else
		data->color = data->rgb.positive;
}

void	color_negatives(t_data *data)
{
	if (data->c.color_current != NULL)
		data->color = ft_atoi_base(data->c.color_current, 16);
	else
		data->color = data->rgb.negative;
}

void	color_connection(t_data *data)
{
	if (data->c.color_current != NULL && data->c.color_next != NULL)
		data->color = ft_atoi_base(data->c.color_current, 16);
	else
		data->color = data->rgb.connection;
}
