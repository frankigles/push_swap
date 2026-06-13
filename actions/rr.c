/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:58:30 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 18:13:59 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Rotate stack a and stack b at the same time. */

int	rr(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	if ((ft_lstsize(*stack_a) < 2) || (ft_lstsize(*stack_b) < 2))
		return (-1);
	rotate(stack_a);
	rotate(stack_b);
	write(1, "rr\n", 3);
	flags->rr++;
	flags->total_ops++;
	return (0);
}
