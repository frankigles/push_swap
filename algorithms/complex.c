/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 20:55:28 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/10 18:53:53 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_max_pos(t_list *stack)
{
	int	max_val;
	int	idx;
	int	max_pos;

	if (!stack)
		return (-1);
	max_val = stack->val;
	idx = 0;
	max_pos = 0;
	while (stack)
	{
		if (stack->val > max_val)
		{
			max_val = stack->val;
			max_pos = idx;
		}
		stack = stack->next;
		idx++;
	}
	return (max_pos);
}

/* chunk = 15 for small stacks (≤100 elements), 30 for bigger ones.
i tracks the next number we want to "place" in order.
We push numbers in rough groups so that stack B ends up somewhat sorted
(smallest at the bottom). */

/* if ((*stack_a)->val <= i) - This is the next number we want right now */
/* else if ((*stack_a)->val <= i + chunk) - This number belongs to
the current chunk*/
/* else - This number is too big (future chunk)*/

void	push_to_b_rolling(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	int	i;
	int	chunk;
	int	loop_guard;

	loop_guard = 0;
	i = 0;
	chunk = 30;
	if (ft_lstsize(*stack_a) <= 100)
		chunk = 15;
	while (*stack_a)
	{
		if ((*stack_a)->idx <= i + chunk)
		{
			pb(stack_a, stack_b, flags);
			if ((*stack_b)->idx < i)
				rb(stack_b, flags);
			i++;
		}
		else
		{
			ra(stack_a, flags);
		}
	}
}
/* max_pos = find_max_pos(*stack_b) - Find index of the biggest number in B */
/* if (max_pos <= size / 2) - Choose the shortest path (rb or rrb)
 to bring max to top*/

void	push_back_to_a(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	int	size;
	int	max_pos;
	int	rotations;

	while (*stack_b)
	{
		size = ft_lstsize(*stack_b);
		max_pos = find_max_pos(*stack_b);
		if (max_pos <= size / 2)
		{
			while (max_pos-- > 0)
				rb(stack_b, flags);
		}
		else
		{
			rotations = size - max_pos;
			while (rotations-- > 0)
				rrb(stack_b, flags);
		}
		pa(stack_a, stack_b, flags);
	}
}

void	index_stack(t_list *stack)
{
	t_list	*current;
	t_list	*compare;
	int		index;

	current = stack;
	while (current)
	{
		index = 0;
		compare = stack;
		while (compare)
		{
			if (current->val > compare->val)
				index++;
			compare = compare->next;
		}
		current->idx = index;
		current = current->next;
	}
}


void	chunk_quick_sort(t_list **stack_a, t_list **b, t_flags *flags)
{
	index_stack(*stack_a);
	push_to_b_rolling(stack_a, b, flags);
	push_back_to_a(stack_a, b, flags);
}

/*1. index_stack - This function uses a nested loop structure to normalize the stack values into sequential ranks
from 0 to N - 1.
Outer Loop: Iterates through every node in the list > N times.
Inner Loop: For every single node, it traverses the entire stack from the beginning to compare values > N times.
Total Operations = N x N = N^2

Therefore, the time complexity of the indexing phase is O(N^2).*/
