/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:08:43 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/13 13:13:15 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	null_check(int fd, void *ptr, int wcount)
{
	int	temp;

	if (ptr)
	{
		temp = ft_putstr_pf(fd, "0x");
		wcount = temp + ft_putaddress(fd, ptr, wcount);
	}
	else
		wcount = ft_putstr_pf(fd, "(nil)");
	return (wcount);
}

static int	argument_manager(int fd, char c, va_list *arg)
{
	int	wcount;

	wcount = 0;
	if (c == 'c')
		wcount = ft_putchar_pf(fd, va_arg(*arg, int));
	else if (c == 's')
		wcount = ft_putstr_pf(fd, va_arg(*arg, char *));
	else if (c == 'p')
		wcount = null_check(fd, va_arg(*arg, void *), wcount);
	else if (c == 'd' || c == 'i')
		wcount = ft_putnbr_pf(fd, va_arg(*arg, int), wcount);
	else if (c == 'u')
		wcount = ft_putunbr(fd, va_arg(*arg, unsigned int), wcount);
	else if (c == 'x' || c == 'X')
		wcount = ft_puthex(fd, va_arg(*arg, unsigned int), c != 'X', wcount);
	else if (c == '%')
		wcount = ft_putchar_pf(fd, '%');
	else
		wcount = -1;
	return (wcount);
}

int	ft_printf(int fd, const char *str, ...)
{
	size_t		i;
	int			wcount;
	int			temp;
	va_list		arg;

	i = -1;
	wcount = 0;
	if (!str)
		return (-1);
	va_start(arg, str);
	while (str && str[++i])
	{
		if (str[i] == '%')
			temp = argument_manager(fd, str[++i], &arg);
		else
			temp = ft_putchar_pf(fd, str[i]);
		if (temp == -1)
		{
			va_end(arg);
			return (-1);
		}
		wcount += temp;
	}
	va_end(arg);
	return (wcount);
}
