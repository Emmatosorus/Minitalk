/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:38:24 by epolitze          #+#    #+#             */
/*   Updated: 2023/11/16 14:43:29 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		len;

	ptr = (char *)s;
	len = 0;
	while (*ptr != '\0')
	{
		ptr++;
		len++;
	}
	while (*ptr != (char)c && len > 0)
	{
		ptr--;
		len--;
		if (*ptr == (char)c)
			return (ptr);
	}
	if (*ptr == (char)c)
		return (ptr);
	return (NULL);
}
