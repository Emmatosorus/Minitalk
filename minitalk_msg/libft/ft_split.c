/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:53:24 by epolitze          #+#    #+#             */
/*   Updated: 2023/11/16 14:38:59 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(char const *str, char sep)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != sep && (str[i + 1] == sep || str[i + 1] == 0))
			j++;
		i++;
	}
	return (j);
}

static void	ft_free(char **splits, size_t j)
{
	while (j-- != 0)
		free(splits[j]);
	free(splits);
}

static int	ft_skip_sep(size_t i, char sep, char const *str)
{
	while (str[i] == sep)
		i++;
	return (i);
}

static int	ft_split_asssit(size_t wc, char const *str, char sep, char **splits)
{
	size_t	i;
	size_t	j;
	size_t	count;

	i = 0;
	j = 0;
	while (str[i] != '\0' && wc != 0 && wc != j)
	{
		count = 0;
		i = ft_skip_sep(i, sep, str);
		while (str[i] != sep && str[i] != '\0')
		{
			count++;
			i++;
		}
		splits[j] = (char *)malloc(count + 1 * sizeof(char));
		if (!splits[j])
		{
			ft_free(splits, j);
			return (-1);
		}
		ft_strlcpy(splits[j], (str + (i - count)), count + 1);
		j++;
	}
	return (0);
}

char	**ft_split(char const *str, char sep)
{
	size_t	wcount;
	char	**splits;

	wcount = ft_word_count(str, sep);
	splits = (char **)ft_calloc((wcount + 1), sizeof(char *));
	if (!splits)
		return (NULL);
	if (ft_split_asssit(wcount, str, sep, splits) == -1)
		return (NULL);
	return (splits);
}
