/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_sort.utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 18:30:44 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/18 22:24:19 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*find_min(t_list *stack)
{
	t_list	*min;

	if (!stack)
		return (NULL);
	min = stack;
	while (stack)
	{
		if (stack->val < min->val)
			min = stack;
		stack = stack->next;
	}
	return (min);
}

t_list	*find_max(t_list *stack)
{
	t_list	*max;

	if (!stack)
		return (NULL);
	max = stack;
	while (stack)
	{
		if (stack->val > max->val)
			max = stack;
		stack = stack->next;
	}
	return (max);
}

/*
** Finds the correct landing spot for a node in the opposite stack.
** Mode 'b' (Phase 1: A -> B): Finds the CLOSEST SMALLER number in B.
** Why? We want Stack B sorted DESCENDING (largest at top) so it's easy
** to push back.
** Fallback: If the value is smaller than anything in B, it belongs on top
** of the MAX value.
** Mode 'a' (Phase 2: B -> A): Finds the CLOSEST BIGGER number in A.
** Why? We want Stack A sorted ASCENDING (smallest at top).
** Fallback: If the value is bigger than anything in A, it belongs on top
** of the MIN value.
*/
// (mode == 'b' && curr->val < val)
// Targets the closest smaller number in B for Phase 1
// (mode == 'a' && curr->val > val)
// Targets the closest bigger number in A for Phase 2
t_list	*get_target(t_list *stack, int val, char mode)
{
	t_list	*curr;
	t_list	*target;

	curr = stack;
	target = NULL;
	while (curr)
	{
		if (mode == 'b' && curr->val < val)
		{
			if (!target || curr->val > target->val)
				target = curr;
		}
		else if (mode == 'a' && curr->val > val)
		{
			if (!target || curr->val < target->val)
				target = curr;
		}
		curr = curr->next;
	}
	if (!target && mode == 'b')
		return (find_max(stack));
	if (!target && mode == 'a')
		return (find_min(stack));
	return (target);
}

/* Calculates moves needed: positive for ra, negative for rra */
/* (+ = forward, - = backward) */

int	get_moves(t_list *stack, t_list *target)
{
	int		pos;
	int		size;
	t_list	*curr;

	size = ft_lstsize(stack);
	pos = 0;
	curr = stack;
	while (curr && curr != target)
	{
		pos++;
		curr = curr->next;
	}
	if (!curr || !target)
		return (-1);
	if (pos <= size / 2)
		return (pos);
	return (pos - size);
}

/* Calculates absolute cost for comparison */
int	get_cost(t_list *a, t_list *b, t_list *node)
{
	int	cost_a;
	int	cost_b;

	cost_a = get_moves(a, node);
	cost_b = get_moves(b, get_target(b, node->val, 'b'));
	if (cost_a < 0)
		cost_a = -cost_a;
	if (cost_b < 0)
		cost_b = -cost_b;
	return (cost_a + cost_b);
}
