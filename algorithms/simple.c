/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 19:23:17 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/18 20:47:59 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	int	ft_find_min_pos(t_list **stack_a)
{
	t_list	*curr_node;
	int		min_value;
	int		min_pos;
	int		curr_pos;

	curr_node = (*stack_a)->next;
	min_value = (*stack_a)->val;
	min_pos = 0;
	curr_pos = 1;
	while (curr_node != NULL)
	{
		if (curr_node->val < min_value)
		{
			min_value = curr_node->val;
			min_pos = curr_pos;
		}
		curr_node = curr_node->next;
		curr_pos++;
	}
	return (min_pos);
}

void	ft_min_extraction(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	int	min_pos;
	int	size;

	size = ft_lstsize(*stack_a);
	min_pos = ft_find_min_pos(stack_a);
	if (min_pos <= (size / 2))
	{
		while (min_pos--)
			ra(stack_a, flags);
	}
	else
	{
		while (min_pos++ < size)
			rra(stack_a, flags);
	}
	pb(stack_a, stack_b, flags);
}

void	ft_sort_three(t_list **stack_a, t_flags *flags)
{
	int	a;
	int	b;
	int	c;

	a = (*stack_a)->val;
	b = (*stack_a)->next->val;
	c = (*stack_a)->next->next->val;
	if (a < b && b < c)
		return ;
	if (a > b && b > c)
	{
		sa(stack_a, flags);
		rra(stack_a, flags);
	}
	else if (a > b && a > c && c > b)
		ra(stack_a, flags);
	else if (a < b && a > c)
		rra(stack_a, flags);
	else if (a > b && a < c && b < c)
		sa(stack_a, flags);
	else
	{
		sa(stack_a, flags);
		ra(stack_a, flags);
	}
}

void	ft_simple(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	int	size_b;

	if (ft_lstsize(*stack_a) == 2)
	{
		sa(stack_a, flags);
		return ;
	}
	while (ft_lstsize(*stack_a) > 3)
		ft_min_extraction(stack_a, stack_b, flags);
	ft_sort_three(stack_a, flags);
	size_b = ft_lstsize(*stack_b);
	while (size_b--)
		pa(stack_a, stack_b, flags);
}
