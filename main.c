/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraigles <fraigles@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 18:11:23 by jmielcar          #+#    #+#             */
/*   Updated: 2026/06/25 23:16:48 by fraigles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	handle_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		write(2, &msg[i++], 1);
	write(2, "\n", 1);
	exit(1);
}

void	free_stack(t_list **stack)
{
	t_list	*current;
	t_list	*next;

	if (!stack || !*stack)
		return ;
	current = *stack;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}

int	init(t_list **stack, char **argv, t_flags *flags)
{
	int		i;
	int		j;
	char	**split_ar;

	argv = parse_flags(argv, flags);
	if (!argv || !*argv)
		return (0);
	i = 0;
	while (argv[i])
	{
		split_ar = ft_split(argv[i++], ' ');
		if (!split_ar[0])
			return (free_string(split_ar), free_stack(stack), 0);
		j = 0;
		while (split_ar[j])
		{
			if (!ft_isnum(split_ar[j]) || !ft_lstadd_back(stack, split_ar[j]))
				return (free_string(split_ar), free_stack(stack), 0);
			j++;
		}
		free_string(split_ar);
	}
	if (!*stack)
		return (0);
	return (1);
}

void	alg_sele(t_list **stack_a, t_list **stack_b, float dis, t_flags *flags)
{
	if (!*stack_a || !(*stack_a)->next)
		return ;
	if (flags->simple)
		ft_simple(stack_a, stack_b, flags);
	if (flags->medium)
		chunk_sort(stack_a, stack_b, flags);
	if (flags->complex)
		ft_radix_sort(stack_a, stack_b, flags);
	if (flags->adaptive && dis < 0.2)
		return (insert_sort(stack_a, stack_b, flags));
	if (flags->adaptive && dis < 0.5)
		return (chunk_sort(stack_a, stack_b, flags));
	if (flags->adaptive)
		ft_radix_sort(stack_a, stack_b, flags);
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	float	disorder;
	t_flags	flags;

	if (argc < 2)
		return (-1);
	argv++;
	stack_a = NULL;
	stack_b = NULL;
	if (!init(&stack_a, argv, &flags))
	{
		free_stack(&stack_a);
		return (handle_error("Error"), -1);
	}
	disorder = compute_disorder(&stack_a);
	if (!is_sorted(&stack_a))
		alg_sele(&stack_a, &stack_b, disorder, &flags);
	if (flags.bench)
		print_bench(disorder, &flags);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
