/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:23:57 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/10 21:41:32 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	compute_disorder(t_list **stack_a)
{
	int		mistakes;
	int		total_pairs;
	t_list	*curr;
	t_list	*next_node;

	mistakes = 0;
	total_pairs = 0;
	curr = (*stack_a);
	while (curr->next)
	{
		next_node = curr->next;
		while (next_node)
		{
			total_pairs++;
			if (curr->val > next_node->val)
				mistakes++;
			next_node = next_node->next;
		}
		curr = curr->next;
	}
	return ((float) mistakes / total_pairs);
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
