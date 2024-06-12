/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:08:59 by nlewicki          #+#    #+#             */
/*   Updated: 2024/05/02 12:16:17 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_specifier(const char c, va_list arg)
{
	char	*str;

	if (c == 's')
	{
		str = va_arg(arg, char *);
		if (str == NULL)
			return (ft_putstr_pf_fd("(null)", 1));
		else
			return (ft_putstr_pf_fd(str, 1));
	}
	else if (c == 'd')
		return (ft_putnbr_pf_fd(va_arg(arg, int), 1));
	else if (c == 'c')
		return (ft_putchar_pf_fd(va_arg(arg, int), 1));
	else if (c == 'i')
		return (ft_putnbr_pf_fd(va_arg(arg, int), 1));
	else if (c == 'x')
		return (ft_putnbr_bas(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (ft_putnbr_bas(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	else if (c == 'u')
		return (ft_putnbr_bas(va_arg(arg, unsigned int), "0123456789"));
	else if (c == '%')
		return (ft_putchar_pf_fd('%', 1));
	return (0);
}

static int	ft_format(const char c, va_list arg)
{
	int		count;
	void	*ptr;
	char	*str;

	str = "0123456789abcdef";
	count = 0;
	if (c == 'p')
	{
		ptr = va_arg(arg, void *);
		if (ptr == NULL)
			return (ft_putstr_pf_fd("0x0", 1));
		else
		{
			ft_putstr_pf_fd("0x", 1);
			return (ft_putnbr_bas((unsigned long long)ptr, str) + 2);
		}
	}
	else
		count = ft_specifier(c, arg);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		count;

	va_start(arg, format);
	i = 0;
	count = 0;
	get_error(0, 1);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
				break ;
			count += ft_format(format[i], arg);
		}
		else
			count += ft_putchar_pf_fd(format[i], 1);
		if (get_error(0, 0) == -1)
			return (-1);
		i++;
	}
	va_end(arg);
	return (count);
}

// int	main(void)
// {
// 	int	i;

// 	i = 42;
// 	ft_printf("!!!My printf!!!\n");
// 	ft_printf("Hallo Welt %d %d %d\n", i, i ,i);
// 	ft_printf("Hallo Welt %s\n", "Hallo");
// 	ft_printf("Hallo Welt %c\n", 'H');
// 	ft_printf("Hallo Welt %p\n", "16");
// 	ft_printf("Hallo Welt %i\n", i);
// 	ft_printf("Hallo Welt %x\n", 42);
// 	ft_printf("Hallo Welt %X\n", 42);
// 	ft_printf("Hallo Welt %u\n", 42);
// 	ft_printf("Hallo Welt %%\n");
// 	printf("!!!The real printf!!!\n");
// 	printf("Hallo Welt %d\n", i);
// 	printf("Hallo Welt %s\n", "Hallo");
// 	printf("Hallo Welt %c\n", 'H');
// 	printf("Hallo Welt %p\n", "16");
// 	printf("Hallo Welt %i\n", i);
// 	printf("Hallo Welt %x\n", 42);
// 	printf("Hallo Welt %X\n", 42);
// 	printf("Hallo Welt %u\n", 42);
// 	printf("Hallo Welt %%\n");

// 	return (0);
// }
