/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:39:44 by jmielcar          #+#    #+#             */
/*   Updated: 2026/05/06 15:03:38 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if (*s == (char) c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen((char *) s);
	if (start >= str_len)
		len = 0;
	if (len > str_len - start)
		len = str_len - start;
	sub_str = ft_calloc(len + 1, sizeof(char));
	if (!sub_str)
		return (0);
	i = 0;
	while (i < len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*result;
	size_t	i;

	result = malloc(count * size);
	if (!result)
		return (NULL);
	i = 0;
	while (i < count * size)
		result[i++] = '\0';
	return (result);
}
