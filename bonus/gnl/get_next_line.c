/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:39:48 by jmielcar          #+#    #+#             */
/*   Updated: 2026/05/12 22:04:14 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file(int fd, char *static_buf)
{
	char	*read_buf;
	char	*tmp;
	ssize_t	bytes_read;

	read_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(read_buf), free(static_buf), NULL);
		if (bytes_read == 0)
			break ;
		read_buf[bytes_read] = '\0';
		tmp = ft_strjoin(static_buf, read_buf);
		free(static_buf);
		static_buf = tmp;
		if (ft_strchr(read_buf, '\n'))
			break ;
	}
	return (free(read_buf), static_buf);
}

static char	*extract_line(char *static_buf)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!static_buf[i])
		return (NULL);
	while (static_buf[i] && static_buf[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (static_buf[i] && static_buf[i] != '\n')
	{
		line[i] = static_buf[i];
		i++;
	}
	if (static_buf[i] && static_buf[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*update_static_buf(char *static_buf)
{
	size_t	i;
	char	*new_static;

	i = 0;
	while (static_buf[i] && static_buf[i] != '\n')
		i++;
	if (!static_buf[i])
		return (free(static_buf), NULL);
	new_static = ft_substr(static_buf, i + 1, (ft_strlen(static_buf) - i + 1));
	return (free(static_buf), new_static);
}

char	*get_next_line(int fd)
{
	static char	*static_buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(static_buf), static_buf = NULL, NULL);
	if (!static_buf)
	{
		static_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!static_buf)
			return (NULL);
	}
	static_buf = read_file(fd, static_buf);
	if (!static_buf)
		return (NULL);
	line = extract_line(static_buf);
	static_buf = update_static_buf(static_buf);
	return (line);
}
