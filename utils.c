/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:58:50 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/10 17:53:14 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	ft_atoi(const char *str)
{
	long	number;
	int		sign;

	number = 0;
	sign = 1;
	while (*str && (*str == ' ' || (*str >= '\t' && *str <= '\r')))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = (number * 10) + (*str - '0');
		str++;
	}
	return (number * sign);
}

int	ft_isnum(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '-')
		i++;
	while (num[i])
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	is_sorted(t_list **stack)
{
	t_list	*current;

	if (!*stack)
		return (1);
	current = *stack;
	while (current->next)
	{
		if (current->val > current->next->val)
			return (0);
		current = current->next;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	free_string(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
