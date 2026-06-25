/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmielcar <jmielcar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:11:38 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/25 17:34:51 by jmielcar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_flags(t_flags *flags)
{
	flags->simple = 0;
	flags->medium = 0;
	flags->complex = 0;
	flags->adaptive = 0;
	flags->bench = 0;
	flags->total_ops = 0;
	flags->sa = 0;
	flags->sb = 0;
	flags->ss = 0;
	flags->pa = 0;
	flags->pb = 0;
	flags->ra = 0;
	flags->rb = 0;
	flags->rr = 0;
	flags->rra = 0;
	flags->rrb = 0;
	flags->rrr = 0;
	flags->chunks = 0;
	flags->num_chunks = 0;
	flags->total_size = 0;
}

static int	count_algo_flags(t_flags *flags)
{
	return (flags->simple + flags->medium + flags->complex + flags->adaptive);
}

char	**parse_flags(char **argv, t_flags *flags)
{
	init_flags(flags);
	while (*argv)
	{
		if (ft_strcmp(*argv, "--simple") == 0)
			flags->simple += 1;
		else if (ft_strcmp(*argv, "--medium") == 0)
			flags->medium += 1;
		else if (ft_strcmp(*argv, "--complex") == 0)
			flags->complex += 1;
		else if (ft_strcmp(*argv, "--adaptive") == 0)
			flags->adaptive += 1;
		else if (ft_strcmp(*argv, "--bench") == 0 && flags->bench++ == 0)
			;
		else
			break ;
		if (count_algo_flags(flags) > 1 || flags->bench > 1)
			return (handle_error("Error"), NULL);
		argv++;
	}
	if (count_algo_flags(flags) == 0)
		flags->adaptive = 1;
	return (argv);
}
