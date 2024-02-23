/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:10:13 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/13 13:10:34 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "../libft.h"

int		ft_printf(int fd, const char *str, ...);
int		ft_putchar_pf(int fd, char c);
int		ft_putstr_pf(int fd, char *str);
int		ft_putaddress(int fd, void *ptr, int wcount);
int		ft_putnbr_pf(int fd, long long n, int wcount);
int		ft_putunbr(int fd, unsigned long int n, int wcount);
int		ft_puthex(int fd, unsigned long int nb, int lower, int wcount);

#endif