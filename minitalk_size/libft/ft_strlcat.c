/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:40 by epolitze          #+#    #+#             */
/*   Updated: 2023/11/16 14:41:23 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;

	i = 0;
	destlen = 0;
	srclen = ft_strlen(src);
	while (dest[destlen] && destlen < n)
		destlen++;
	if (n == 0)
		return (destlen + srclen);
	while (src[i] && i + destlen + 1 < n)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	if (destlen < n)
		dest[destlen + i] = '\0';
	return (destlen + srclen);
}
