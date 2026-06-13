/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 20:57:09 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/11 20:12:17 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Simultaneously rotates both stacks to save massive moves
void	rot_both(t_list **a, t_list **b, t_list *cheapest, t_flags *f)
{
	int		m_a;
	int		m_b;
	t_list	*target_b;

	target_b = get_target(*b, cheapest->val, 'b');
	m_a = get_moves(*a, cheapest);
	m_b = get_moves(*b, target_b);
	while (*a != cheapest && *b != target_b && m_a > 0 && m_b > 0)
	{
		rr(a, b, f);
	}
	while (*a != cheapest && *b != target_b && m_a <= 0 && m_b <= 0)
	{
		rrr(a, b, f);
	}
}

/*
** Rotates a single stack ('a' or 'b') until the target node reaches the top.
** Uses the sign of get_moves (positive = forward/ra/rb, negative = reverse/rra/rrb).
*/

void	rot_stack(t_list **s, t_list *target, char name, t_flags *f)
{
	int	moves;

	moves = get_moves(*s, target);
	while (*s != target)
	{
		if (moves > 0)
		{
			if (name == 'a')
				ra(s, f);
			else
				rb(s, f);
		}
		else
		{
			if (name == 'a')
				rra(s, f);
			else
				rrb(s, f);
		}
	}
}
/*
** Phase 1 Engine: Finds the node in A that requires the fewest combined
** operations to be put into its correct sorted position inside Stack B.
** Combines matching rotations using rot_both, finishes individual rotations,
** and pushes the node.
*/
/* Finds the cheapest element in A to push to B
(the one that requires the least total rotations in both stacks),
then performs the rotations and push. */

// Optimization: Simultaneously rotate both stacks if moving in the same direction
// rot_both(stack_a, stack_b, cheapest, flags);
// Rot stack_a till cheapest on top which we push to stack_b;
// rot_stack(stack_a, cheapest, 'a', flags);
// Rot stack_b till find smallest in stack_b but bigger than top of stack_a
// rot_stack(stack_b, get_target(*stack_b, cheapest->val, 'b'), 'b', flags);

void	push_cheapest(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	t_list	*curr;
	t_list	*cheapest;
	int		min_cost;
	int		current_cost;

	curr = *stack_a;
	min_cost = 2147483647;
	while (curr)
	{
		current_cost = get_cost(*stack_a, *stack_b, curr);
		if (current_cost < min_cost)
		{
			min_cost = current_cost;
			cheapest = curr;
		}
		curr = curr->next;
	}
	rot_both(stack_a, stack_b, cheapest, flags);
	rot_stack(stack_a, cheapest, 'a', flags);
	rot_stack(stack_b, get_target(*stack_b, cheapest->val, 'b'), 'b', flags);
	pb(stack_a, stack_b, flags);
}
/*
** Main Min/Max Sort (Turk Sort) Algorithm Control Flow:
** 1. Seed Stack B with 2 elements to establish a min/max baseline.
** 2. Phase 1 (A -> B): Greedily push elements to B, maintaining a rough descending order.
** 3. Phase 2 (B -> A): Safely bring the correct insertion spot to the top of A and push back.
** 4. Clean up: Final shift to ensure the absolute smallest value is on top of Stack A.
*/

/* rot_stack(stack_a, target, 'a', flags)
rotates stack A until that correct insertion position is on top.*/

/* rot_stack(stack_a, find_min(*stack_a), 'a', flags)
final move to make sure the smallest number is on top of A*/

void	insert_sort(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	int		size;
	t_list	*target;

	size = ft_lstsize(*stack_a);
	if (size < 2)
		return ;
	pb(stack_a, stack_b, flags);
	if (size > 2)
		pb(stack_a, stack_b, flags);
	while (*stack_a)
		push_cheapest(stack_a, stack_b, flags);
	while (*stack_b)
	{
		target = get_target(*stack_a, (*stack_b)->val, 'a');
		rot_stack(stack_a, target, 'a', flags);
		pa(stack_a, stack_b, flags);
	}
	rot_stack(stack_a, find_min(*stack_a), 'a', flags);
}
