/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:32:07 by nlewicki          #+#    #+#             */
/*   Updated: 2024/07/01 09:48:11 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_digit(char c, int digits_in_base)
{
	if (digits_in_base <= 10)
	{
		if (c >= '0' && c < '0' + digits_in_base)
			return (c - '0');
		else
			return (-1);
	}
	else
	{
		if (c >= '0' && c <= '9')
			return (c - '0');
		else if (c >= 'a' && c < 'a' + digits_in_base - 10)
			return (c - 'a' + 10);
		else
			return (-1);
	}
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	sign;
	int	digit;

	result = 0;
	sign = 1;
	if (*str == '0' && *(str + 1) == 'x')
		str += 2;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	digit = get_digit(ft_tolower(*str), str_base);
	while (digit >= 0)
	{
		result = result * str_base + digit;
		++str;
		digit = get_digit(ft_tolower(*str), str_base);
	}
	return (result * sign);
}
