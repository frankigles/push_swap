/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 19:24:26 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/25 17:34:54 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*check_strategy(t_flags *flags, float disorder)
{
	if (flags->complex)
		return ("Complex / O(n log n)");
	if (flags->medium)
		return ("Medium / O(n√n)");
	if (flags->simple)
		return ("Simple / O(n\xC2\xB2)");
	if (disorder < 0.2)
		return ("Adaptive / O(n\xC2\xB2)");
	if (disorder >= 0.2 && disorder < 0.5)
		return ("Adaptive / O(n√n)");
	return ("Adaptive / O(n log n)");
}

void	print_bench(float disorder, t_flags *f)
{
	char	*action1;
	char	*action2;

	action1 = "[bench] sa: %d sb: %d ss: %d pa: %d pb: %d\n";
	action2 = "[bench] ra: %d rb: %d rr: %d rra: %d rrb: %d rrr: %d\n";
	ft_printf_fd(2, "[bench] disorder: %f%%\n", (disorder / 1) * 100);
	ft_printf_fd(2, "[bench] strategy: %s\n", check_strategy(f, disorder));
	ft_printf_fd(2, "[bench] total_ops: %d\n", f->total_ops);
	ft_printf_fd(2, action1, f->sa, f->sb, f->ss, f->pa, f->pb);
	ft_printf_fd(2, action2, f->ra, f->rb, f->rr, f->rra, f->rrb, f->rrr);
}
