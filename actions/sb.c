/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:57:17 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 18:21:32 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Swaps the head and the second node in stack b. */

int	sb(t_list **stack_b, t_flags *flags)
{
	if (swap(stack_b) == -1)
		return (-1);
	write(1, "sb\n", 3);
	flags->sb++;
	flags->total_ops++;
	return (0);
}
