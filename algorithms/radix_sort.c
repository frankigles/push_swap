/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:39:26 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/09 21:52:10 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(t_list *stack)
{
	int	max;
	int	bits;

	max = stack->val;
	bits = 0;
	while (stack)
	{
		if (stack->val > max)
			max = stack->val;
		stack = stack->next;
	}
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	ft_radix_sort(t_list **a, t_list **b, t_flags *flags)
{
	int		i;
	int		j;
	int		size;
	int		max_bits;

	size = ft_lstsize(*a);
	max_bits = get_max_bits(*a);
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if (!(((*a)->val >> i) & 1))
				pb(a, b, flags);
			else
				ra(a, flags);
			j++;
		}
		while (*b)
			pa(a, b, flags);
		if (is_sorted(a))
			break ;
		i++;
	}
}
