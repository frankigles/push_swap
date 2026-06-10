/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:56:27 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/09 19:42:16 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_min_val(t_list *stack)
{
	int	min;

	min = stack->val;
	while (stack)
	{
		if (stack->val < min)
			min = stack->val;
		stack = stack->next;
	}
	return (min);
}

int	find_max_val(t_list *stack)
{
	int	max;

	max = stack->val;
	while (stack)
	{
		if (stack->val > max)
			max = stack->val;
		stack = stack->next;
	}
	return (max);
}

int	get_pos(t_list *stack, t_list *target)
{
	int	i;

	i = 0;
	if (!target)
		return (-1);
	while (stack)
	{
		if (stack == target)
			return (i);
		stack = stack->next;
		i++;
	}
	return (-1);
}

/* Calculates moves needed: positive for ra, negative for rra */
/* (+ = forward, - = backward) */

int	get_moves(t_list *stack, t_list *target)
{
	int	pos;
	int	size;

	pos = get_pos(stack, target);
	size = ft_lstsize(stack);
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
	cost_b = get_moves(b, get_target(b, node->val));
	if (cost_a < 0)
		cost_a = -cost_a;
	if (cost_b < 0)
		cost_b = -cost_b;
	return (cost_a + cost_b);
}
