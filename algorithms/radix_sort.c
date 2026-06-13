/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:39:26 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/11 19:56:22 by jmielcar         ###   ########.fr       */
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
	int	max_bits;

	size = ft_lstsize(*a);
	index_stack(*a);
	max_bits = get_max_bits(size);
	i = 0;
	while (i < max_bits)
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

// static void	sort_array(int *arr, int size)
// {
// 	int	i;
// 	int	j;
// 	int	tmp;

// 	i = 0;
// 	while (i < size - 1)
// 	{
// 		j = 0;
// 		while (j < size - i - 1)
// 		{
// 			if (arr[j] > arr[j + 1])
// 			{
// 				tmp = arr[j];
// 				arr[j] = arr[j + 1];
// 				arr[j + 1] = tmp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	idx_stack(t_list *stack, int size)
// {
// 	t_list	*curr;
// 	int		*arr;
// 	int		i;

// 	arr = malloc(sizeof(int) * size);
// 	if (!arr)
// 		return ;
// 	curr = stack;
// 	i = 0;
// 	while (curr)
// 	{
// 		arr[i++] = curr->val;
// 		curr = curr->next;
// 	}
// 	sort_array(arr, size);
// 	curr = stack;
// 	while (curr)
// 	{
// 		i = 0;
// 		while (i < size && curr->val != arr[i])
// 			i++;
// 		curr->idx = i;
// 		curr = curr->next;
// 	}
// 	free(arr);
// }
