/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:01:28 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/13 13:13:37 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_pf(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_pf(int fd, char *str)
{
	int	temp;

	if (str)
		temp = write(fd, str, ft_strlen(str));
	else
		temp = write(fd, "(null)", 6);
	return (temp);
}

int	ft_putnbr_pf(int fd, long long n, int wcount)
{
	int	temp;
	int	temp2;

	temp = 0;
	if (n < 0)
	{
		temp = ft_putchar_pf(fd, '-');
		if (temp == -1)
			return (-1);
		n *= -1;
	}
	if (n > 9)
	{
		wcount = ft_putnbr_pf(fd, n / 10, wcount);
		temp2 = ft_putchar_pf(fd, n % 10 + '0');
		if (temp2 == -1)
			return (-1);
	}
	else
		temp2 = ft_putchar_pf(fd, n % 10 + '0');
	if (temp == -1 || temp2 == -1)
		return (-1);
	wcount += (temp + temp2);
	return (wcount);
}

int	ft_putunbr(int fd, unsigned long int n, int wcount)
{
	int	temp;

	if (n > 9)
	{
		wcount = ft_putunbr(fd, n / 10, wcount);
		temp = ft_putchar_pf(fd, n % 10 + '0');
		if (temp == -1)
			return (-1);
	}
	else
		temp = ft_putchar_pf(fd, n % 10 + '0');
	if (temp == -1)
		return (-1);
	wcount += temp;
	return (wcount);
}
