/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 20:57:09 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/10 21:16:42 by jmielcar         ###   ########.fr       */
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

/* if (curr->val > val_b && curr->val < best_match)
Find the smallest number in A that is still bigger than val_b*/

t_list	*get_target(t_list *stack_a, int val_b)
{
	t_list	*curr;
	t_list	*target;
	long	best_match;

	curr = stack_a;
	target = NULL;
	best_match = 2147483648LL;
	while (curr)
	{
		if (curr->val > val_b && curr->val < best_match)
		{
			best_match = curr->val;
			target = curr;
		}
		curr = curr->next;
	}
	if (!target)
		return (find_min(stack_a));
	return (target);
}

/* Rotates stack based on the signed move count.
Until the target is at the top */

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
/* Finds the cheapest element in A to push to B
(the one that requires the least total rotations in both stacks),
then performs the rotations and push. */

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
	// Rot stack_a till cheapest on top which we push to stack_b;
	rot_stack(stack_a, cheapest, 'a', flags);
	// Rot stack_b till find smallest in stack_b but bigger than top of stack_a
	rot_stack(stack_b, get_target(*stack_b, cheapest->val), 'b', flags);
	pb(stack_a, stack_b, flags);
}

/* rot_stack(stack_a, get_target(*stack_a, (*stack_b)->val), 'a', flags)
rotates stack A until that correct insertion position is on top.*/

/* rot_stack(stack_a, find_min(*stack_a), 'a', flags)
final move to make sure the smallest number is on top of A*/

void	min_max_sort(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	int	size;

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
		// Rotate stack_a till min val on top but bigger than max val in stack_b
		rot_stack(stack_a, get_target(*stack_a, (*stack_b)->val), 'a', flags);
		pa(stack_a, stack_b, flags);
	}
	rot_stack(stack_a, find_min(*stack_a), 'a', flags);
}
