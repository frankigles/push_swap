/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:39:26 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/18 22:22:32 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int	get_max_bits(int size)
{
	int	max;
	int	bits;

	max = size - 1;
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

void	ft_radix_sort(t_list **a, t_list **b, t_flags *flags)
{
	int	i;
	int	j;
	int	size;

	size = ft_lstsize(*a);
	if (size < 10)
		return (ft_simple(a, b, flags));
	index_stack(*a);
	i = 0;
	while (i < get_max_bits(size))
	{
		if (is_sorted(a))
			break ;
		j = -1;
		while (++j < size)
		{
			if (!(((*a)->idx >> i) & 1))
				pb(a, b, flags);
			else
				ra(a, flags);
		}
		while (*b)
			pa(a, b, flags);
		i++;
	}
}
