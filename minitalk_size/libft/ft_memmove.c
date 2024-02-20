/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:37:07 by epolitze          #+#    #+#             */
/*   Updated: 2023/11/16 14:23:17 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destc;
	unsigned char	*srcc;

	destc = (unsigned char *)dest;
	srcc = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (destc < srcc)
		while (n--)
			*destc++ = *srcc++;
	else
		while (n--)
			*(destc + n) = *(srcc + n);
	return (dest);
}
