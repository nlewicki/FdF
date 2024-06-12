/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_bas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:47:58 by nlewicki          #+#    #+#             */
/*   Updated: 2024/05/02 12:16:49 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_valid_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	if (!base || !base[0] || !base[1])
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	ft_is_zero(unsigned long long nbr, char *base, int *i, char *str)
{
	if (nbr == 0)
	{
		str[0] = base[0];
		(*i)++;
	}
}

int	ft_putnbr_bas(unsigned long long nbr, char *base)
{
	size_t	base_size;
	char	*str;
	int		i;
	int		count;

	count = 0;
	base_size = 0;
	if (!is_valid_base(base))
		return (0);
	while (base[base_size] != '\0')
		base_size++;
	str = (char *)malloc(sizeof(char) * (base_size + 1));
	if (str == NULL)
		return (get_error(-1, 0));
	i = 0;
	ft_is_zero(nbr, base, &i, str);
	while (nbr > 0)
	{
		str[i++] = base[nbr % base_size];
		nbr /= base_size;
	}
	while (i > 0)
		count += ft_putchar_pf_fd(str[--i], 1);
	free(str);
	return (count);
}
