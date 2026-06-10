/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:57:35 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 18:26:28 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Swaps the head and the second node in stack a. */

int	sa(t_list **stack_a, t_flags *flags)
{
	if (swap(stack_a) == -1)
		return (-1);
	write(1, "sa\n", 3);
	flags->sa++;
	flags->total_ops++;
	return (0);
}
