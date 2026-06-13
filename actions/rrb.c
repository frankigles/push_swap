/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:58:00 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 18:14:07 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Reverse rotate stack a. */

int	rrb(t_list **stack_b, t_flags *flags)
{
	if (rev_rotate(stack_b) == -1)
		return (-1);
	write(1, "rrb\n", 4);
	flags->rra++;
	flags->total_ops++;
	return (0);
}
