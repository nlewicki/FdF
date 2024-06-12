/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr__pf_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:47:28 by nlewicki          #+#    #+#             */
/*   Updated: 2024/04/29 11:41:06 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_pf_fd(int n, int fd)
{
	char	c;
	int		count;

	count = 0;
	if (n == -2147483648)
		return (ft_putstr_pf_fd("-2147483648", fd));
	if (n < 0)
	{
		ft_putchar_pf_fd('-', fd);
		count++;
		n = -n;
	}
	if (n > 9)
		count += ft_putnbr_pf_fd(n / 10, fd);
	c = n % 10 + '0';
	ft_putchar_pf_fd(c, fd);
	count++;
	return (count);
}
