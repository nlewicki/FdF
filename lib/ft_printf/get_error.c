/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:29:06 by nlewicki          #+#    #+#             */
/*   Updated: 2024/04/03 11:26:17 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_error(int status, int intial)
{
	static int	error;

	if (intial == 1)
		error = 0;
	if (error == -1)
		return (-1);
	else if (status < 0)
		error = -1;
	return (error);
}
