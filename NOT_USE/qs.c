/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:40:21 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/11 20:01:57 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_pivot(t_list *stack, int size)
{
	t_list	*curr;
	t_list	*compare;
	int		smaller_count;
	int		target_smaller;

	target_smaller = size / 2;
	curr = stack;
	while (curr)
	{
		smaller_count = 0;
		compare = stack;
		while (compare)
		{
			if (compare->val < curr->val)
				smaller_count++;
			compare = compare->next;
		}
		if (smaller_count == target_smaller)
			return (curr->val);
		curr = curr->next;
	}
	return (stack->val);
}

int	partition_a(t_list **a, t_list **b, int size, t_flags *flags)
{
	int	pushed;
	int	rotated;
	int	pivot;

	pivot = find_pivot(*a, size);
	pushed = 0;
	rotated = 0;
	while (size--)
	{
		if ((*a)->val < pivot)
		{
			pb(a, b, flags);
			pushed++;
		}
		else
		{
			ra(a, flags);
			rotated++;
		}
	}
	while (rotated--)
		rra(a, flags);
	return (pushed);
}

int	partition_b(t_list **a, t_list **b, int size, t_flags *flags)
{
	int	pushed;
	int	rotated;
	int	pivot;

	pivot = find_pivot(*b, size);
	pushed = 0;
	rotated = 0;
	while (size--)
	{
		if ((*b)->val >= pivot)
		{
			pa(a, b, flags);
			pushed++;
		}
		else
		{
			rb(b, flags);
			rotated++;
		}
	}
	while (rotated--)
		rrb(b, flags);
	return (pushed);
}

void	quick_sort_b(t_list **a, t_list **b, int size, t_flags *flags);

/* quick_sort_a(a, b, size - pushed, flags)
Recursive call on the remaining upper half in A */
/* quick_sort_b(a, b, pushed, flags)
Recursive call on the lower half pushed to B */
void	quick_sort_a(t_list **a, t_list **b, int size, t_flags *flags)
{
	int	pushed;

	if (size <= 1)
		return ;
	if (size == 2)
	{
		if ((*a)->val > (*a)->next->val)
			sa(a, flags);
		return ;
	}
	pushed = partition_a(a, b, size, flags);
	quick_sort_a(a, b, size - pushed, flags);
	quick_sort_b(a, b, pushed, flags);
}

/* quick_sort_a(a, b, pushed, flags)
Process the elements sent back to A */
/* quick_sort_b(a, b, size - pushed, flags)
Process the elements remaining in B */

void	quick_sort_b(t_list **a, t_list **b, int size, t_flags *flags)
{
	int	pushed;

	if (size <= 0)
		return ;
	if (size == 1)
	{
		pa(a, b, flags);
		return ;
	}
	if (size == 2)
	{
		if ((*b)->val < (*b)->next->val)
			sb(b, flags);
		pa(a, b, flags);
		pa(a, b, flags);
		return ;
	}
	pushed = partition_b(a, b, size, flags);
	quick_sort_a(a, b, pushed, flags);
	quick_sort_b(a, b, size - pushed, flags);
}
