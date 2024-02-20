/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:10:30 by epolitze          #+#    #+#             */
/*   Updated: 2023/11/16 13:42:39 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlen(long int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t		count;
	long int	nlong;
	char		*number;

	count = 0;
	nlong = n;
	count = ft_nlen(nlong);
	number = ft_calloc(count + 1, sizeof(char));
	if (!number)
		return (NULL);
	if (nlong < 0)
	{
		nlong *= -1;
		number[0] = '-';
	}
	while (count-- > 0 && n != 0 && number[count] != '-')
	{
		number[count] = (nlong % 10) + 48;
		nlong = nlong / 10;
	}
	if (n == 0)
		number[0] = '0';
	return (number);
}
