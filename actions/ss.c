/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ss.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:54:50 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 18:21:23 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Swaps the head and the second node in stack a and stack b a the same time. */

int	ss(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	if ((ft_lstsize(*stack_a) < 2) || (ft_lstsize(*stack_b) < 2))
		return (-1);
	swap(stack_a);
	swap(stack_b);
	write(1, "sa\n", 3);
	flags->ss++;
	flags->total_ops++;
	return (0);
}
