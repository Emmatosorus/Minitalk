/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolitze <epolitze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:57:54 by epolitze          #+#    #+#             */
/*   Updated: 2024/02/13 14:35:51 by epolitze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_get_cr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

static char	*read_more(int fd, char *line, char *buffer, ssize_t *read_len)
{
	ssize_t	llen;
	ssize_t	blen;
	char	*new_line;

	llen = 0;
	if (line)
		llen = ft_strlen(line);
	blen = ft_strlen(buffer);
	new_line = (char *)malloc((llen + blen + 1) * sizeof(char));
	if (!new_line)
		return (free(line), NULL);
	new_line[llen + blen] = '\0';
	ft_strncpy(new_line, line, llen);
	ft_strncpy(new_line + llen, buffer, blen);
	free(line);
	*read_len = read(fd, buffer, BUFFER_SIZE);
	if (*read_len == -1)
		return (NULL);
	buffer[*read_len] = '\0';
	line = new_line;
	return (line);
}

static char	*get_line_buf(char *line, char *buffer)
{
	ssize_t	cr_pos;
	ssize_t	llen;
	ssize_t	blen;
	char	*new_line;

	llen = 0;
	if (line)
		llen = ft_strlen(line);
	cr_pos = ft_get_cr(buffer, '\n') + 1;
	new_line = (char *)malloc((llen + cr_pos + 1) * sizeof(char));
	if (!new_line)
		return (free(line), NULL);
	new_line[llen + cr_pos] = '\0';
	ft_strncpy(new_line, line, llen);
	ft_strncpy(new_line + llen, buffer, cr_pos);
	blen = ft_strlen(buffer);
	ft_memmove(buffer, buffer + cr_pos, blen - cr_pos);
	buffer[blen - cr_pos] = '\0';
	free(line);
	line = new_line;
	return (line);
}

static char	*read_line(int fd, char *line, char *buffer, ssize_t *read_len)
{
	if (buffer[0] == '\0')
	{
		*read_len = read(fd, buffer, BUFFER_SIZE);
		if (*read_len < 1)
			return (free(line), NULL);
		buffer[*read_len] = '\0';
	}
	while (ft_get_cr(buffer, '\n') == -1)
	{
		line = read_more(fd, line, buffer, read_len);
		if (!line || *read_len == -1)
			return (NULL);
		if (*read_len == 0)
			return (line);
	}
	line = get_line_buf(line, buffer);
	if (!line)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	ssize_t		read_len;
	static char	buffer[1024][BUFFER_SIZE + 1];

	line = NULL;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		buffer[fd][0] = '\0';
		return (NULL);
	}
	read_len = BUFFER_SIZE;
	if (ft_get_cr(buffer[fd], '\n') >= 0)
		line = get_line_buf(line, buffer[fd]);
	else
		line = read_line(fd, line, buffer[fd], &read_len);
	if (!line || read_len == -1)
	{
		buffer[fd][0] = '\0';
		return (free(line), NULL);
	}
	return (line);
}
