/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:59:01 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 17:52:23 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ra(t_list **stack_a, t_flags *flags)
{
	if (rotate(stack_a) == -1)
		return (-1);
	write(1, "ra\n", 3);
	flags->ra++;
	flags->total_ops++;
	return (0);
}
