/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:58:16 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 18:14:04 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Reverse rotate stack a. */

int	rra(t_list **stack_a, t_flags *flags)
{
	if (rev_rotate(stack_a) == -1)
		return (-1);
	write(1, "rra\n", 4);
	flags->rra++;
	flags->total_ops++;
	return (0);
}
