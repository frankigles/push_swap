/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:48:29 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 18:04:49 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* It first finds the last and second-to-last nodes,
detaches the last node, then links it as the new head. */

int	rev_rotate(t_list **stack)
{
	t_list	*last;
	t_list	*prev_last;

	if (!*stack || !(*stack)->next)
		return (-1);
	last = ft_lstlast(*stack);
	prev_last = *stack;
	while (prev_last->next != last)
		prev_last = prev_last->next;
	prev_last->next = NULL;
	last->next = *stack;
	*stack = last;
	return (0);
}
