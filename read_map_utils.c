/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:35:51 by nlewicki          #+#    #+#             */
/*   Updated: 2024/07/03 12:53:04 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

int	get_line_width(char *line)
{
	int	width;
	int	in_number;
	int	i;

	width = 0;
	in_number = 0;
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != ' ' && !in_number)
		{
			width++;
			in_number = 1;
		}
		else if (line[i] == ' ')
		{
			in_number = 0;
		}
		i++;
	}
	return (width);
}

void	map_is_empty(t_data *data)
{
	ft_printf("Error: Map is empty\n");
	free_data(data);
	exit(EXIT_FAILURE);
}

void	clean_up(t_read *read)
{
	if (read->fd != -1)
		close(read->fd);
}

void	map_error(t_read *read)
{
	ft_printf("(%d instead of %d)\n",
		read->current_width, read->expected_width);
	if (read->map_lines != NULL)
		ft_free(read->ind, read->map_lines);
	clean_up(read);
	exit(EXIT_FAILURE);
}

void	check_map(t_read *read, t_data *data)
{
	if (read->expected_width == -1)
	{
		read->expected_width = read->current_width;
		data->point.x = read->current_width;
	}
	else if (read->current_width != read->expected_width)
	{
		map_error(read);
	}
}
