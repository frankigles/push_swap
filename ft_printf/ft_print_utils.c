/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 20:41:37 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/09 21:23:50 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	count;

	if (str == NULL)
		return (ft_putstr_fd("(null)", fd));
	count = 0;
	while (*str)
	{
		write(fd, str, 1);
		count++;
		str++;
	}
	return (count);
}

int	ft_putnbr_fd(long nbr, int fd)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
		len = 1;
	}
	if (nbr >= 10)
		len += ft_putnbr_fd(nbr / 10, fd);
	len += write(fd, &"0123456789"[nbr % 10], 1);
	return (len);
}

int	ft_puthex_fd(unsigned long long nb, int is_uppercase, int fd)
{
	unsigned long long	count;

	count = 0;
	if (nb >= 16)
		count += ft_puthex_fd(nb / 16, is_uppercase, fd);
	if (is_uppercase)
		write(fd, &"0123456789ABCDEF"[nb % 16], 1);
	else
		write(fd, &"0123456789abcdef"[nb % 16], 1);
	count++;
	return (count);
}

int	ft_putptr_fd(void *ptr, int fd)
{
	if (ptr == NULL)
		return (ft_putstr_fd("(nil)", fd));
	return (ft_putstr_fd("0x", fd) + ft_puthex_fd((unsigned long) ptr, 0, fd));
}

int	ft_putfloat_fd(double num, int precision, int fd)
{
	int			count;
	long long	int_p;
	double		round;

	count = 0;
	if (num < 0 && ++count)
		write(fd, "-", 1);
	if (num < 0)
		num = -num;
	round = 0.5;
	int_p = precision;
	while (int_p--)
		round /= 10.0;
	num += round;
	int_p = (long long)num;
	count += ft_putnbr_fd(int_p, fd);
	if (precision > 0 && ++count)
		write(fd, ".", 1);
	while (precision-- > 0)
	{
		num = (num - int_p) * 10;
		int_p = (int)num;
		count += ft_putnbr_fd(int_p, fd);
	}
	return (count);
}
