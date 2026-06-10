/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:10:35 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/10 21:44:45 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Checks if any node in the stack falls within the value range
int	has_value_in_range(t_list *stack, int min, int max)
{
	while (stack)
	{
		if (stack->val >= min && stack->val <= max)
			return (1);
		stack = stack->next;
	}
	return (0);
}

// Finds the position of the closest node that matches the value range
/* if (first_pos == -1)
mark just once first_pos */
/* if (first_pos <= (size - last_pos))
if we are closer to top with first element we just do forward rotation*/
int	find_closest_val_pos(t_list *stack, int min, int max)
{
	int	first_pos;
	int	last_pos;
	int	i;
	int	size;

	size = ft_lstsize(stack);
	first_pos = -1;
	last_pos = -1;
	i = 0;
	while (stack)
	{
		if (stack->val >= min && stack->val <= max)
		{
			if (first_pos == -1)
				first_pos = i;
			last_pos = i;
		}
		stack = stack->next;
		i++;
	}
	if (first_pos <= (size - last_pos))
		return (first_pos);
	return (last_pos);
}

/* if (pos <= size / 2) - Choose the shortest path (rb or rrb)
 to bring max to top*/
/* if (ft_lstsize(*b) > 1 && (*b)->val < chunk_mid)
Optimization: If pushed value is smaller than the chunk midpoint, rotate B */

void	push_to_b(t_list **a, t_list **b, t_range range, t_flags *flags)
{
	int	pos;
	int	size;
	int	chunk_mid;

	chunk_mid = range.min + ((range.max - range.min) / 2);
	while (has_value_in_range(*a, range.min, range.max))
	{
		pos = find_closest_val_pos(*a, range.min, range.max);
		size = ft_lstsize(*a);
		if (pos <= size / 2)
			while (pos--)
				ra(a, flags);
		else
			while (size - pos++)
				rra(a, flags);
		pb(a, b, flags);
		if (ft_lstsize(*b) > 1 && (*b)->val < chunk_mid)
			rb(b, flags);
	}
}

void	push_back_to_a_nor(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	int	size;
	int	max_pos;

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
			while (max_pos++ < size)
				rrb(stack_b, flags);
		}
		pa(stack_a, stack_b, flags);
	}
}

/* chunk_step = (max_val - min_val) / flags->num_chunks;
Calculate how wide each value chunk is */
/* if (i == flags->num_chunks - 1 || range.max > max_val)
Make sure the last chunk catches everything up to the absolute max */

void	chunk_sort(t_list **a, t_list **b, t_flags *flags)
{
	int		min_val;
	int		max_val;
	t_range	range;
	int		chunk_step;
	int		i;

	min_val = find_min_val(*a);
	max_val = find_max_val(*a);
	flags->num_chunks = ft_sqrt(ft_lstsize(*a));
	// flags->num_chunks = 11;
	// if (ft_lstsize(*a) <= 100)
	// 	flags->num_chunks = 5;
	chunk_step = (max_val - min_val) / flags->num_chunks;
	if (chunk_step == 0)
		chunk_step = 1;
	range.min = min_val;
	i = 0;
	while (i++ < flags->num_chunks)
	{
		range.max = range.min + chunk_step;
		if (i == flags->num_chunks - 1 || range.max > max_val)
			range.max = max_val;
		push_to_b(a, b, range, flags);
		range.min = range.max + 1;
	}
	push_back_to_a_nor(a, b, flags);
}
