/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:59:32 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 17:51:42 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	pa(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	if (push(stack_a, stack_b) == -1)
		return (-1);
	write(1, "pa\n", 3);
	flags->pa++;
	flags->total_ops++;
	return (0);
}
