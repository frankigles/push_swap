/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 20:59:12 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/09 20:01:14 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* It first checks that there are at least 2 elements,
then swaps the data between the head and the second node. */

int	swap(t_list **stack)
{
	t_list	*first;
	t_list	*second;

	if (!*stack || !(*stack)->next)
		return (-1);
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
	return (0);
}
