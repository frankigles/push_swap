/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 20:00:37 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/09 20:12:58 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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

t_list	*ft_lstnew(int value)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->val = value;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_lsthas(t_list *head, int value)
{
	while (head)
	{
		if (head && head->val == value)
			return (1);
		head = head->next;
	}
	return (0);
}

int	ft_lstadd_back(t_list **stack, char *c)
{
	t_list	*last_node;
	t_list	*new_node;
	long	num;

	num = ft_atoi(c);
	if (num < -2147483647 || num > 2147483647 || ft_lsthas(*stack, (int)num))
		return (0);
	new_node = ft_lstnew(num);
	if (!new_node)
		return (free_stack(stack), 0);
	if (!*stack)
	{
		*stack = new_node;
		return (1);
	}
	last_node = ft_lstlast(*stack);
	last_node->next = new_node;
	return (1);
}
