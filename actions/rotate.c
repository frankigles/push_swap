/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:45:29 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 18:05:43 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* It updates the head to the second node,
links the old last node to the old first,
and makes the old first the new tail. */

int	rotate(t_list **stack)
{
	t_list	*first;
	t_list	*last;

	if (!*stack || !(*stack)->next)
		return (-1);
	first = *stack;
	last = ft_lstlast(*stack);
	*stack = first->next;
	last->next = first;
	first->next = NULL;
	return (0);
}
