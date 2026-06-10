/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:44:42 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 20:53:43 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static char	*ft_strdup(const char *s)
{
	int		i;
	int		str_len;
	char	*ptr_str;
	char	*str_dup;

	ptr_str = (char *) s;
	str_len = 0;
	while (ptr_str[str_len])
		str_len++;
	str_dup = malloc(sizeof(char) * (str_len + 1));
	if (!str_dup)
		return (0);
	i = 0;
	while (i < str_len)
	{
		str_dup[i] = s[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	str_len;
	size_t	i;

	if (!s)
		return (NULL);
	str_len = 0;
	while (s[str_len])
		str_len++;
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	sub_str = malloc(sizeof(char) * (len + 1));
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

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	**ft_free_split(char **split, int i)
{
	while (i > 0)
		free(split[--i]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_words(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		result[j++] = ft_substr(s, start, i - start);
		if (!result[j - 1])
			return (ft_free_split(result, j - 1));
	}
	result[j] = NULL;
	return (result);
}
