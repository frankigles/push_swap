/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:45:26 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/18 23:40:38 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	convert(char spec, va_list *arg, int fd)
{
	int	c;

	if (spec == 's')
		return (ft_putstr_fd(va_arg(*arg, char *), fd));
	if (spec == 'p')
		return (ft_putptr_fd(va_arg(*arg, void *), fd));
	if (spec == 'd' || spec == 'i')
		return (ft_putnbr_fd(va_arg(*arg, int), fd));
	if (spec == 'u')
		return (ft_putnbr_fd(va_arg(*arg, unsigned int), fd));
	if (spec == 'x' || spec == 'X')
		return (ft_puthex_fd(va_arg(*arg, unsigned int), spec == 'X', fd));
	if (spec == 'f')
		return (ft_putfloat_fd(va_arg(*arg, double), 2, fd));
	if (spec == 'c')
	{
		c = va_arg(*arg, int);
		return (write(fd, &c, 1));
	}
	if (spec == '%')
		return (write(fd, "%", 1));
	return (0);
}

int	ft_printf_fd(int fd, char const *str, ...)
{
	va_list			argptr;
	unsigned int	count;

	va_start(argptr, str);
	count = 0;
	while (str && *str)
	{
		if (*str == '%')
		{
			str++;
			if (!*str)
				break ;
			count += convert(*str, &argptr, fd);
			str++;
		}
		else
		{
			count += write(fd, str, 1);
			str++;
		}
	}
	va_end(argptr);
	return (count);
}
