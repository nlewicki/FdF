/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:24:02 by nlewicki          #+#    #+#             */
/*   Updated: 2024/10/30 09:30:40 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FdF.h"

void	free_data(t_data *data)
{
	free_point(data);
	free_color(data);
}

void	free_point(t_data *data)
{
	int	i;

	i = 0;
	if (data->point.z != NULL)
	{
		while (i < data->point.y)
		{
			if (data->point.z[i] != NULL)
				free(data->point.z[i]);
			i++;
		}
		free(data->point.z);
		data->point.z = NULL;
	}
}

void	free_color(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->point.color != NULL)
	{
		while (i < data->point.y)
		{
			j = 0;
			if (data->point.color[i] != NULL)
			{
				while (j < data->point.x)
				{
					if (data->point.color[i][j] != NULL)
						free(data->point.color[i][j]);
					j++;
				}
				free(data->point.color[i]);
			}
			i++;
		}
		free(data->point.color);
		data->point.color = NULL;
	}
}

void	ft_free(int j, char **result)
{
	if (result == NULL)
		return ;
	while (j >= 0)
	{
		free(result[j]);
		j--;
	}
	free(result);
}
