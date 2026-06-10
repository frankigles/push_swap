/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:58:48 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 17:52:26 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rb(t_list **stack_b, t_flags *flags)
{
	if (rotate(stack_b) == -1)
		return (-1);
	write(1, "rb\n", 3);
	flags->rb++;
	flags->total_ops++;
	return (0);
}
