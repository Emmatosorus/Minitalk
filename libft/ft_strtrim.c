/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:08:22 by epolitze          #+#    #+#             */
/*   Updated: 2023/11/16 11:56:02 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	totrim(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

static char	*emptystr(void)
{
	char	*empty;

	empty = ft_calloc(1, sizeof(char));
	if (!empty)
		return (NULL);
	return (empty);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	start = 0;
	end = (ft_strlen(s1) - 1);
	if (!s1 || !set)
		return (NULL);
	while (totrim(s1[start], set))
		start++;
	if (start == end + 1)
		return (emptystr());
	while (totrim(s1[end], set))
		end--;
	str = (char *)malloc((end - start) + 2 * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (s1 + start), (end - start) + 2);
	return (str);
}
