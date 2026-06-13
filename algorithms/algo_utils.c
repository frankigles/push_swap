/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:56:27 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/11 20:30:39 by jmielcar         ###   ########.fr       */
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

int	ft_sqrt(int number)
{
	long	res;

	if (number < 0)
		return (0);
	if (number == 0 || number == 1)
		return (number);
	res = 1;
	while (res * res <= number)
		res++;
	return ((int)res - 1);
}
