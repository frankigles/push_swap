/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:59:44 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/09 20:34:30 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_print_stack(t_list *stack_a, char *name)
{
	ft_printf_fd(1, "****** STACK %s ******\n", name);
	while (stack_a)
	{
		ft_printf_fd(1, "val: %d", stack_a->val);
		if (stack_a->next)
			ft_printf_fd(1, " -> ");
		else
			ft_printf_fd(1, " -> NULL\n");
		stack_a = stack_a->next;
	}
	ft_printf_fd(1, "*********************\n\n");
}

void	print_flags(t_flags *flags)
{
	ft_printf_fd(1, "****** FLAGS ******\n");
	ft_printf_fd(1, "f simple: %d\n", flags->simple);
	ft_printf_fd(1, "f medium: %d\n", flags->medium);
	ft_printf_fd(1, "f complex: %d\n", flags->complex);
	ft_printf_fd(1, "f adaptive: %d\n", flags->adaptive);
	ft_printf_fd(1, "f bench: %d\n", flags->bench);
	ft_printf_fd(1, "*******************\n\n");
}
