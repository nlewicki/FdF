/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlewicki <nlewicki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:17:34 by nlewicki          #+#    #+#             */
/*   Updated: 2024/05/02 12:16:24 by nlewicki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <ctype.h>

int		ft_putchar_pf_fd(char c, int fd);
int		ft_putstr_pf_fd(char *s, int fd);
int		ft_putnbr_pf_fd(int n, int fd);
int		ft_putnbr_bas(unsigned long long n, char *base);
int		ft_printf(const char *format, ...);
int		get_error(int status, int intial);

#endif
