/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraigles <fraigles@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:23:57 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/25 22:57:34 by fraigles         ###   ########.fr       */
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
	if (!curr)
		return (0.0);
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
	if (total_pairs == 0)
		return (0.0);
	return ((float) mistakes / total_pairs);
}
