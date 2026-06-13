/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:59:17 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/08 17:51:46 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	pb(t_list **stack_a, t_list **stack_b, t_flags *flags)
{
	if (push(stack_b, stack_a) == -1)
		return (-1);
	write(1, "pb\n", 3);
	flags->pb++;
	flags->total_ops++;
	return (0);
}
